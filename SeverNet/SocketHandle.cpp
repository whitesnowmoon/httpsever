#include "SocketHandle.h"

SocketHandle::SocketHandle()
	:PORT(0), listenSocket(SEVER_SOCKET_ERROR),IP(""), ApplicationTpye(APPICANTION_LAYER_TYPE::_ORIGIN_)
{
}

SocketHandle::SocketHandle(SEVERIP IP, SEVERPORT PORT, SEVERSOCKET listenSocket,  APPICANTION_LAYER_TYPE ApplicationTpye)
	:IP(IP), PORT(PORT), listenSocket(listenSocket), ApplicationTpye(ApplicationTpye)
{
}
