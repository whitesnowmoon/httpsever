#include "SeverSocketOpen.h"
#include<chrono>

SeverSocketOpen* SeverSocketOpen::instance=nullptr;
SeverSocketOpen::~SeverSocketOpen() {

}
void SeverSocketOpen::run() {
	SeverThreadPool* pool = SeverThreadPool::Get_SeverThreadPool_Instance();
	for (size_t i = 0; i < socketHandles.size(); i++)
	{
		for (size_t j = 0; j < std::thread::hardware_concurrency()/ socketHandles.size(); j++)
		{
			SeverHttpHandle* htc = new SeverHttpHandle(socketHandles[i]);
			htc->setCallback(callBackFun);
			pool->push_task(htc);
		}
	}
	//SeverHttpHandle* htc = new SeverHttpHandle(socketHandles[1]);
	//htc->setCallback(callBackFun);
	//pool->push_task(htc);

}
SeverSocketOpen* SeverSocketOpen::Get_SeverSocket_Instance() {
	static clear clr_SeverSocket;
	if (instance == nullptr)
		instance = new SeverSocketOpen();
	return instance;
}

int SeverSocketOpen::_init_(const std::vector<SocketHandle>& Handles) {
	this->socketHandles = Handles;
	SeverSocket::_init_();
	for (auto handle = socketHandles.begin(); handle != socketHandles.end(); handle++)
	{
		_SEVERADDRESS_ addr;
		addr.severFamily = SEVER_AF_INET;
		addr.severIp = handle->IP;
		addr.severPort = handle->PORT;
		handle->listenSocket = SeverSocket::severmakesocketTCP();
		if (SeverSocket::severbind(handle->listenSocket, addr) == SEVER_SOCKET_ERROR)return false;
		if(SeverSocket::severlisten(handle->listenSocket, 10) == SEVER_SOCKET_ERROR)return false;
	}
	return true;
}

int SeverSocketOpen::setCallback(Callback_Funtion fun) {
	if (fun == nullptr) {
		return false;
	}
	this->callBackFun = fun;
	return true;
}



