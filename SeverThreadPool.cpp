#include "SeverThreadpool.h"
SeverThreadPool* SeverThreadPool::instance = nullptr;
SeverThreadPool::SeverThreadPool() :running_flag_(true) {
	int count = std::thread::hardware_concurrency();
	for (int i = 0; i < count; i++)
	{
		threads.emplace_back(&SeverThreadPool::work, this);
	}
	this->thead_num_ = this->threads.size();
	std::cout << "Pool thread sum=" << this->threads.size() << "\n";
}

SeverThreadPool::~SeverThreadPool() {
	running_flag_ = false;
	cv_.notify_all();
	for (auto& th : threads) {
		if (th.joinable()) {
			th.join();
		}
	}
	for (auto& start_task: start_severtasks)
	{
		start_task->destroy();
		std::cout << start_task << "delete\n";
	}
}

void SeverThreadPool::push_task(SeverTask* task) {
	std::unique_lock<std::mutex> unlock(this->mtx_);
	this->severtasks.push(task);
	this->cv_.notify_one();
}

SeverThreadPool* SeverThreadPool::Get_SeverThreadPool_Instance() {
	static clear clr_SeverThreadPool;
	if (!instance)
		instance = new SeverThreadPool();
	return instance;
}

int SeverThreadPool::Get_CurTask_num() {
	return this->severtasks.size();
}

void SeverThreadPool::work() {
	while (true) {
		if (!running_flag_) {
			return;
		}
		SeverTask* task = nullptr;
		{
			std::unique_lock<std::mutex> unlock(this->mtx_);
			cv_.wait(unlock, [&] {
				return !severtasks.empty() || !running_flag_;
				});
			if (running_flag_) {
				if (this->severtasks.size() != 0)
					task = this->severtasks.front();
				this->severtasks.pop();
				start_severtasks.push_back(task);
			}
		}
		if (task != nullptr) {
			task->run();
		}
	}
}