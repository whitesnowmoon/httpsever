#include "SeverAppSocket.h"

SeverAppSocket::SeverAppSocket(SocketApp sockapp):SocketApp(sockapp) {
}
bool SeverAppSocket::SSL_init_() {
	ssl = SSL_new(SeverSSL::ctx);
	if (this->clientSocket == SEVER_SOCKET_ERROR) {
		return false;
	}
	SSL_set_fd(ssl, this->clientSocket);
	if (SeverSSL::SSLaccept(ssl) <0) {
		return false;;
	}
	return true;
}




