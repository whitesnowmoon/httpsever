#ifndef APPSOCKHANDLE_H
#define APPSOCKHANDLE_H

#include"SeverAppSocket.h"

class AppSockHandle :public SeverAppSocket
{
public:
	AppSockHandle(SocketApp sockapp);
	virtual int App_recv(char* buff, int len) override;
	virtual int App_send(char* buff, int len) override;
	virtual int App_close() override;
	virtual int App_recv_peek(char* buff, int len) override;
};

#endif // !APPSOCKHANDLE_H
