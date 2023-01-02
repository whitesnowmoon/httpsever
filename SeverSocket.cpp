#include "SeverSocket.h"
#include "SeverHttp.h"
#include<stdio.h>
SeverSocket* SeverSocket::instance = nullptr;
SeverSocket::SeverSocket() {
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("Error at WSAStartup()\n");
		Sleep(1000);
		_exit(0);
	}

	ListenSocket_TCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket_TCP == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		Sleep(1000);
		_exit(0);

	}
	sockaddr_in service = { 0 };
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = htonl(INADDR_ANY);
	service.sin_port = htons(SEVERSOCKET_PORT);
	if (bind(ListenSocket_TCP, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		printf("bind() failed.\n");
		closesocket(ListenSocket_TCP);
		WSACleanup();
		Sleep(1000);
		_exit(0);
	}
	if (listen(ListenSocket_TCP, 8) == SOCKET_ERROR)
	{
		printf("Error listening on socket.\n");
		closesocket(ListenSocket_TCP);
		WSACleanup();
		Sleep(1000);
		_exit(0);
	}

	FD_ZERO(&Sockets_TCP);
	FD_SET(ListenSocket_TCP, &Sockets_TCP);
	printf("sever open\n");

	while (1) {
		timeval time_ = { 1,0 };
		fd_set tempsockets= Sockets_TCP;
		int state = select(0, &tempsockets, nullptr, nullptr, &time_);
		if (state == 0)continue;
		else if (state > 0) {
			int pos_socket=0;
			while (pos_socket!=tempsockets.fd_count)
			{
				if (tempsockets.fd_array[pos_socket] == ListenSocket_TCP) {
					SOCKET socketclient = accept(ListenSocket_TCP,nullptr,nullptr);
					if (INVALID_SOCKET == socketclient)continue;
					FD_SET(socketclient, &Sockets_TCP);
				}
				else
				{
					char buff[1500];
					memset(buff, '\0', 1500);

					int nRecv = recv(tempsockets.fd_array[pos_socket], buff, 1500, MSG_PEEK);
					if (nRecv > 0) {
						SeverHttp sever(tempsockets.fd_array[pos_socket]);
						sever.run();
						
					}
					else if (0 == nRecv) {
						closesocket(tempsockets.fd_array[pos_socket]);
						FD_CLR(tempsockets.fd_array[pos_socket], &Sockets_TCP);
						//printf("exit\n");
					}
					else if(SOCKET_ERROR== nRecv) {
						int error = WSAGetLastError();
						printf("interrupt  Recv error:%d\n", error);
						closesocket(tempsockets.fd_array[pos_socket]);
						FD_CLR(tempsockets.fd_array[pos_socket], &Sockets_TCP);
					}
					else
					{
						printf("system  Recv error");
						return;
					}
				}
				pos_socket++;
			}
		}
		else
		{
			int error = WSAGetLastError();
			printf("select error:%d\n", error);
		}
	}

}

SeverSocket::~SeverSocket() {
	closesocket(ListenSocket_TCP);
	WSACleanup();
}

SeverSocket* SeverSocket::Get_SeverSocket_Instance() {
	static clear clr_SeverSocket;
	if (instance == nullptr)
		instance = new SeverSocket();
	return instance;
}
