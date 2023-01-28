#ifndef SEVERSOCKET_H
#define SEVERSOCKET_H


#define SEVERSOCKETOPEN_PORT 80

#include<iostream>
#include<vector>
#include<thread>
//#include<WinSock2.h>
#include "SeverSocket.h"
//#include<WinSock2.h> �����Ǵ�SeverSocket.h��WinSock2.hһ�����Զ����˰�ȫ��־�������������Ͳ����
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
