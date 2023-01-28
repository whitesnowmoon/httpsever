#ifndef SEVERAPPSOCKET_H
#define SEVERAPPSOCKET_H
#include "SocketApp.h"
#include"SeverSSL.h"

class SeverAppSocket:public SocketApp
{
public:
	SSL* ssl=nullptr;
	SeverAppSocket(SocketApp sockapp);
	virtual ~SeverAppSocket() = default;
	bool SSL_init_();
	virtual int App_recv(char* buff, int len)=0;
	virtual int App_send(char* buff, int len) = 0;
	virtual int App_close() = 0;
	virtual int App_recv_peek(char* buff, int len) = 0;
};


#endif // SEVERAPPSOCKET_H

