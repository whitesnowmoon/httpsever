#ifndef SEVERSOCKET_H
#define SEVERSOCKET_H

#define SEVERSOCKET_PORT 80
#define FD_SETSIZE 32
#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
class SeverSocket
{
private:
	WSADATA wsaData;
	SOCKET ListenSocket_TCP;
	fd_set Sockets_TCP;
	SeverSocket();
	~SeverSocket();
	class clear{                       
	public:
		~clear() {
			if (instance)
				delete instance;
		}
	};
public:
	static SeverSocket* Get_SeverSocket_Instance();
	static SeverSocket* instance;
};

#endif 