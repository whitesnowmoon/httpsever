#ifndef SEVERFILE_H
#define SEVERFILE_H
#include<iostream>
#include<WinSock2.h>
#include<vector>
#include<fstream>
#pragma comment(lib,"Ws2_32.lib")

#define DEBUG
#define _ERROR_ -1

class SeverFile
{
public:
	virtual int SeverFile_send(SOCKET dst);
	virtual bool SeverFile_open(std::string url);
	virtual bool SeverFile_close();
	virtual int SeverFile_recv(SOCKET src) { return 0; }
	virtual int SeverFile_flush() { return 0; }
	int length;
	std::string type;
	int state;
	std::fstream file;
};
#endif

