#include "SeverSocketOpen.h"

#include<stdio.h>
SeverSocketOpen* SeverSocketOpen::instance = nullptr;
SeverSocketOpen::SeverSocketOpen() {
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
	service.sin_port = htons(SEVERSOCKETOPEN_PORT);
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
	printf("sever open\n");


}

SeverSocketOpen::~SeverSocketOpen() {
	closesocket(ListenSocket_TCP);
	WSACleanup();
}

SeverSocketOpen* SeverSocketOpen::Get_SeverSocket_Instance() {
	static clear clr_SeverSocket;
	if (instance == nullptr)
		instance = new SeverSocketOpen();
	return instance;
}

void SeverSocketOpen::run() {

	//for (size_t i = 0; i < 10; i++)
	//{
	//	SeverSocketHandle* task = new SeverSocketHandle(this->ListenSocket_TCP);
	//	SeverThreadPool::Get_SeverThreadPool_Instance()->push_task(task);
	//}
	SeverSocketHandle* task = new SeverSocketHandle(this->ListenSocket_TCP);
	task->run();

	
}
