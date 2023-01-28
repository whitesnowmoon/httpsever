#ifndef SOCKETHANDLE_H
#define SOCKETHANDLE_H
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include"SeverSocket.h"
#pragma comment(lib,"Ws2_32.lib")

enum class  APPICANTION_LAYER_TYPE
{
	_HTTP_ = 0,
	_HTTPS_,
	_ORIGIN_
};

class SocketHandle
{
public:
	SEVERIP IP;
	SEVERPORT PORT;
	SEVERSOCKET listenSocket;
	APPICANTION_LAYER_TYPE ApplicationTpye;
	SocketHandle();
	SocketHandle(SEVERIP IP, SEVERPORT PORT, SEVERSOCKET listenSocket, APPICANTION_LAYER_TYPE ApplicationTpye);
};




#endif // !SOCKETHANDLE_H

