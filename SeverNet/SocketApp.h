#ifndef SOCKETAPP_H
#define SOCKETAPP_H

#include"SocketHandle.h"
#include<openssl/ssl.h>

class SocketApp:public SocketHandle
{
public:
	SEVERSOCKET clientSocket;
	unsigned long RecvOverTime = 2000;
	unsigned long SendOverTime = 100000;
	int socketRecvBuffSize = 65536;
	SocketApp(SocketHandle handle);
};

#endif // !SOCKETAPP_H
