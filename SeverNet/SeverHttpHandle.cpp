#include "SeverHttpHandle.h"
#include"AppSockHandle.h"
#include"AppSSLHandle.h"

SeverHttpHandle::SeverHttpHandle(SocketApp handle):connecthandle(handle),start(true){
}

int SeverHttpHandle::setCallback(Callback_Funtion fun) {
	if (fun == nullptr) {
		return false;
	}
	this->callBackFun = fun;
	return true;
}

void SeverHttpHandle::run() {
	SEVERADDRESS addr;
	start = true; int nRecv;
	while (start)
	{
		std::cout << this->connecthandle.PORT<<"--wait accept--" << std::this_thread::get_id() << "\n";
		this->connecthandle.clientSocket = SeverSocket::severaccept(this->connecthandle.listenSocket, nullptr);
		if (this->connecthandle.clientSocket == -1) {
			//int e = WSAGetLastError();
			return;
		}
		std::cout << "accept---" << std::this_thread::get_id() << "\n";
		unsigned long on_off = 0;
		SeverSocket::setbuffandtime(this->connecthandle.clientSocket, connecthandle.socketRecvBuffSize, connecthandle.RecvOverTime, connecthandle.SendOverTime);
		SeverSocket::severioctlsocket(connecthandle.clientSocket, SEVER_FIONBIO, &on_off);
		if (connecthandle.ApplicationTpye == APPICANTION_LAYER_TYPE::_HTTPS_) {
			httpHandle = new AppSSLHandle(connecthandle);
			if (!httpHandle->SSL_init_()) {
				httpHandle->App_close();
				std::cout << "SSL_init_ error\n";
				break;
			}
		}
		else if (connecthandle.ApplicationTpye == APPICANTION_LAYER_TYPE::_HTTP_) {
			httpHandle = new AppSockHandle(connecthandle);
		}
		else
		{
			break;
		}

		while (true)
		{
			char buff[2048];
			memset(buff, '\0', 2048);
			nRecv = httpHandle->App_recv_peek(buff, 1024);

			if (nRecv > 0) {
				this->callBackFun(httpHandle);                           //Net结束http线程安全
			}
			else if (0 == nRecv) {
				httpHandle->App_close();
				break;
			}
			else if (nRecv < 0) {
				httpHandle->App_close();
				break;
			}
			else
			{
				printf("system  Recv error");
				return;
			}
		}
		delete httpHandle;
		std::cout << "break---" << std::this_thread::get_id() << "\n";
	}
}

void SeverHttpHandle::destroy() {
	start = false;
	delete this;
	std::cout << "delete thread";
	
}
