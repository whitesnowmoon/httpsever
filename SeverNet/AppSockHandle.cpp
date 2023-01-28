#include"AppSockHandle.h"

AppSockHandle::AppSockHandle(SocketApp sockapp) :SeverAppSocket(sockapp) {
}
int AppSockHandle::App_recv(char* buff, int len) {
	return SeverSocket::severrecv(this->clientSocket, buff, len, 0);
}

int AppSockHandle::App_send(char* buff, int len) {
	return SeverSocket::seversend(this->clientSocket, buff, len, 0);
}

int AppSockHandle::App_close() {
	return SeverSocket::severclosesocket(this->clientSocket);
}

int AppSockHandle::App_recv_peek(char* buff, int len) {
	return SeverSocket::severrecv(this->clientSocket, buff, len, SEVER_MSG_PEEK);
}
