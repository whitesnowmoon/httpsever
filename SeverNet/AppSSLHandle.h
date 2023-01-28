#ifndef APPSSLHANDLE_H
#define APPSSLHANDLE_H

#include"SeverAppSocket.h"

class AppSSLHandle :public SeverAppSocket
{
public:
	AppSSLHandle(SocketApp sockapp);
private:
	bool SSL_init_();
	virtual int App_recv(char* buff, int len) override;
	virtual int App_send(char* buff, int len) override;
	virtual int App_close() override;
	virtual int App_recv_peek(char* buff, int len) override;

};


#endif // !APPSSLHANDLE_H

