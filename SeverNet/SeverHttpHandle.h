#ifndef SEVERHTTPHANDLE_H
#define SEVERHTTPHANDLE_H

#include"SocketApp.h"
#include"SeverAppSocket.h"
#include"../SeverThreadPool/SeverThreadpool.h"
#include"SeverSocket.h"
typedef int (*Callback_Funtion)(SeverAppSocket* handle);

class SeverHttpHandle :public SeverTask
{
public:
	typedef int (*Callback_Funtion)(SeverAppSocket* handle);
	SeverHttpHandle(SocketApp handle);
	int setCallback(Callback_Funtion fun);
	virtual void run() override;
	virtual void destroy() override;
	~SeverHttpHandle()=default;
private:
	Callback_Funtion callBackFun;
	SocketApp connecthandle;
	SeverAppSocket* httpHandle = nullptr;
	bool start;
};

#endif // SEVERHTTPHANDLE_H
