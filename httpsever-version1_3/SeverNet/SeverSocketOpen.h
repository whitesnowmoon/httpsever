#ifndef SEVERSOCKETOPEN_H
#define SEVERSOCKETOPEN_H

#define SEVERSOCKETOPEN_PORT 80

#include<WinSock2.h>
#include"../SeverThreadPool/SeverThreadpool.h"
#include"SeverSocketHandle.h"
#pragma comment(lib,"Ws2_32.lib")

class SeverSocketOpen
{
private:
	WSADATA wsaData;
	SOCKET ListenSocket_TCP;
	SeverSocketOpen();
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
	static SeverSocketOpen* Get_SeverSocket_Instance();
	void run();
	static SeverSocketOpen* instance;
};

#endif 

