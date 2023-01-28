#ifndef SEVERSOCKET_H
#define SEVERSOCKET_H


#define SEVERSOCKETOPEN_PORT 80

#include<iostream>
#include<vector>
#include<thread>
//#include<WinSock2.h>
#include "SeverSocket.h"
//#include<WinSock2.h> 下面是打开SeverSocket.h的WinSock2.h一次所以定义了安全标志，上面打开了下面就不会打开
#include"SocketHandle.h"
#include "SocketApp.h"
#include"../SeverThreadPool/SeverThreadpool.h"
#include"SeverHttpHandle.h"


class SeverSocketOpen
{
private:
	std::vector<std::thread> threads;
	static SeverSocketOpen* instance;
	std::vector<SocketHandle> socketHandles;
	SeverSocketOpen()=default;
	~SeverSocketOpen();
	class clear
	{
	public:
		~clear() {
			if (instance)
				delete instance;
		}
	};
public:
	Callback_Funtion callBackFun;
	void run();
	static SeverSocketOpen* Get_SeverSocket_Instance();
	int _init_(const std::vector<SocketHandle>& Handles);
	int setCallback(Callback_Funtion fun);
};

#endif // !SEVERSOCKET_H
