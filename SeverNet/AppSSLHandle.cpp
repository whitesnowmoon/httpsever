#include"AppSSLHandle.h"


AppSSLHandle::AppSSLHandle(SocketApp sockapp) :SeverAppSocket(sockapp) {
}
bool AppSSLHandle::SSL_init_() {
	ssl = SSL_new(SeverSSL::ctx);
	if (this->clientSocket == SEVER_SOCKET_ERROR)
		return false;
	SSL_set_fd(ssl, this->clientSocket);
	if (SeverSSL::SSLaccept(ssl) <= 0) {
		return false;;
	}
	return true;
}

int AppSSLHandle::App_recv(char* buff, int len) {
	return SeverSSL::SSLread(ssl, buff, len, 0);
}

int AppSSLHandle::App_send(char* buff, int len) {
	return SeverSSL::SSLsend(ssl, buff, len, 0);
}

int AppSSLHandle::App_close() {
	int code = SeverSSL::SSLcolse(ssl);
	SeverSocket::severclosesocket(this->clientSocket);
	return code;
}

int AppSSLHandle::App_recv_peek(char* buff, int len) {
	return SSL_peek(ssl,buff,len);
}
