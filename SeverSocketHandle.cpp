#include "SeverSocketHandle.h"
#include<chrono>
SeverSocketHandle::SeverSocketHandle(SOCKET listener_socket) {
	this->listener_socket = listener_socket;
}

void SeverSocketHandle::run() {
	start = true;
	while (start)
	{
		std::cout << "wait accept\n";
		this->cur_socket = accept(this->listener_socket, nullptr, NULL);
		unsigned long on_off = 1;
		while (true)
		{
			char buff[2048];
			memset(buff, '\0', 2048);
			int nRecv = 0,time_=20;
			ioctlsocket(this->cur_socket, FIONBIO, &on_off);
			nRecv = recv(this->cur_socket, buff, 2048, MSG_PEEK);
			while (nRecv==-1)
			{
				std::this_thread::sleep_for(std::chrono::microseconds(time_));
				nRecv = recv(this->cur_socket, buff, 2048, MSG_PEEK);
				time_ +=20;
				if (time_ > 1000) {
					break;
				}
			}
			if (nRecv > 0) {
				SeverRequest Request_tool;
				Request_tool.analysis(this->cur_socket);
				Response* response =Request_tool.creatResponse();
				response->anwser();
				response->destroy();
			}
			else if (0 == nRecv) {
				closesocket(this->cur_socket);
				this->cur_socket = NULL;
				break;
			}
			else if (nRecv<0) {
				int error = WSAGetLastError();
				closesocket(this->cur_socket);
				std::cout << error << "\n";
				this->cur_socket = NULL;
				break;
			}
			else
			{
				printf("system  Recv error");
				return;
			}
		}
	}
}

void SeverSocketHandle::destroy() {
	closesocket(this->cur_socket);
	start = false;
	delete this;
}
