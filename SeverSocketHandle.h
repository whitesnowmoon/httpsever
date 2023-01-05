#ifndef SEVERSOCKETHANDLE_H
#define SEVERSOCKETHANDLE_H

#include<WinSock2.h>
#include"SeverThreadpool.h"
#include"SeverRequest.h"
#include"Get_SeverResponse.h"
class SeverSocketHandle :public SeverTask
{
public:
	SeverSocketHandle(SOCKET listener_socket);
	virtual void run() override;                // ͨ�� SeverTask �̳�
private: 
	void destroy();
	bool start;
	SOCKET cur_socket;
	SOCKET listener_socket;
};

#endif 
