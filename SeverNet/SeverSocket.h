#ifndef _SEVERSOCKET_H
#define _SEVERSOCKET_H

#include<iostream>
#include"../SeverError/SeverError.h"
typedef unsigned int SEVERSOCKET;
typedef unsigned short SEVERNETFAMILY;
typedef unsigned short SEVERPORT;
typedef std::string SEVERIP;

typedef struct _SEVERADDRESS_    //网络地址描述
{
	SEVERIP severIp;
	SEVERPORT severPort;
	SEVERNETFAMILY severFamily;
}SEVERADDRESS;

#define _SEVER_WIN_
#ifdef _SEVER_LINUX_
#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#define SEVER_MSG_PEEK MSG_PEEK 
#define SEVER_FIONBIO FIONBIO 
#define SEVER_AF_INET AF_INET

#endif

#ifdef _SEVER_WIN_
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define SEVER_MSG_PEEK MSG_PEEK 
#define SEVER_FIONBIO FIONBIO 
#define SEVER_AF_INET AF_INET
#define SEVER_SOCKET_ERROR SOCKET_ERROR 

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#endif

class SeverSocket
{
public:
	//内联放在cpp中好像找不到
	static inline int _init_() {
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != NO_ERROR) {
			SeverError::PushError(SEVERERRORCODE::SEVERSOCKETINITERROR);
			return NO_ERROR;
		}
		return 0;
	}
	static inline SEVERSOCKET severmakesocketTCP() {
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == SOCKET_ERROR) {
			SeverError::PushError(SEVERERRORCODE::SEVERADDRESSBINDERROR);
			return SOCKET_ERROR;
		}
		else
		{
			return sock;
		}
	}
	static inline int severbind(SEVERSOCKET sock, const _SEVERADDRESS_& addr) {
		sockaddr_in service = { 0 };
		service.sin_family = addr.severFamily;
		service.sin_addr.s_addr = inet_addr(addr.severIp.c_str());
		service.sin_port = htons(addr.severPort);
		if (bind(sock, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
			closesocket(sock);
			WSACleanup();
			SeverError::PushError(SEVERERRORCODE::SEVERSOCKETINITERROR);
			return SOCKET_ERROR;
		}
		return 0;
	}

	static inline  SEVERSOCKET severaccept(SEVERSOCKET sock, _SEVERADDRESS_* recvaddr) {
		int len; SEVERSOCKET result; 
		sockaddr_in service = { 0 };
		len = sizeof(service);
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = htonl(INADDR_ANY);
		if (recvaddr != NULL) {
			result = accept(sock, (SOCKADDR*)&service, &len);
			if (result == SOCKET_ERROR) {
				recvaddr->severIp.clear();
				recvaddr->severPort = 0;
				recvaddr->severFamily = 0;
				SeverError::PushError(SEVERERRORCODE::SEVERSOCKETACCEPTERROR); 
				return result;
			}
			recvaddr->severFamily = service.sin_family;
			recvaddr->severPort = ntohs(service.sin_port);
			recvaddr->severIp.append(inet_ntoa(service.sin_addr));
		}
		else
		{
			result = accept(sock, NULL, NULL);
			if (result == SOCKET_ERROR) {
				SeverError::PushError(SEVERERRORCODE::SEVERSOCKETACCEPTERROR);
			}
		}
		return result;
	}
	static inline bool setbuffandtime(SEVERSOCKET sock,int size, unsigned long recv_time_temp, unsigned long send_time_temp) {
		DWORD time_r = recv_time_temp;//毫秒		
		DWORD time_s = send_time_temp;//毫秒	
		int optVal = size;//缓冲
		int optLen = sizeof(int);
		int re = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&time_r, sizeof(time_r));
		int rb = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&optVal, optLen);
		int se = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&time_s, time_s);
		if (!re &&!rb&&!se) {
			return true;
		}
		return false;
	}

	static inline int severlisten(SEVERSOCKET sock, int num) {
		int result = 0;
		result = listen(sock, num);
		if (result == SOCKET_ERROR)
		{
			closesocket(sock);
			WSACleanup();
			SeverError::PushError(SEVERERRORCODE::SEVERSOCKETLISTENERROR);
		}
		return result;

	}
	static inline int severrecv(SEVERSOCKET sock,char* buff,int len,int flag) {
		return recv(sock, buff, len, flag);
	}
	static inline int seversend(SEVERSOCKET sock, char* buff, int len, int flag) {
		return send(sock, buff, len, flag);
	}
	static inline  int severioctlsocket(SEVERSOCKET sock,long cmd,unsigned long * argp) {
		int result = ioctlsocket(sock, cmd, argp);
		if (result == SOCKET_ERROR) {
			SeverError::PushError(SEVERERRORCODE::SEVERSOCKETLISTENERROR);
		}
		return result;
	}
	static inline unsigned long severinet_addr(const char* cp) {
		return inet_addr(cp);
	}
	static inline int severclosesocket(SEVERSOCKET sock) {
		return closesocket(sock);
	}
	static bool socket_is_exist(SOCKET sock) {
			bool ret = false;
			HANDLE closeEvent = WSACreateEvent();
			WSAEventSelect(sock, closeEvent, FD_CLOSE);

			DWORD dwRet = WaitForSingleObject(closeEvent, 0);

			if (dwRet == WSA_WAIT_EVENT_0)
				ret = true;
			else if (dwRet == WSA_WAIT_TIMEOUT)
				ret = false;

			WSACloseEvent(closeEvent);
			return ret;
	}

};

#endif // !SEVERSOCKET_H


