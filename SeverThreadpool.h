#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS
#ifndef SEVERTHREADPOOL_H
#define SEVERTHREADPOOL_H
#include<iostream>
#include<mutex>
#include<thread>
#include<queue>
#include<atomic>

class SeverTask
{
public:
	virtual void run() = 0;
	virtual void destroy() = 0;
};
class SeverThreadPool
{
public:
	void push_task(SeverTask* task);
	static SeverThreadPool* Get_SeverThreadPool_Instance();
	int Get_CurTask_num();
private:
	std::atomic<int> thead_num_;
	static SeverThreadPool* instance;
	class clear
	{
	public:
		~clear() {
			if (instance)
				delete instance;
		}
	};
	SeverThreadPool();
	~SeverThreadPool();
	void work();
	std::vector<std::thread> threads;
	std::queue<SeverTask*> severtasks;
	std::vector<SeverTask*> start_severtasks;
	std::atomic_bool running_flag_;
	std::condition_variable cv_;
	std::mutex mtx_;
};

#endif 
