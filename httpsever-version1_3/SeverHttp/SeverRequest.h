#ifndef SEVERREQUEST_H
#define SEVERREQUEST_H

#include<iostream>
#include<WinSock2.h>
#include<map>
#include<string>
#include<vector>
#include"Response.h"

#pragma comment(lib,"Ws2_32.lib")


#define _OK_ 1
#define _ERROR_ -1

#define _ON_ 2
#define _READLY_ 3
#define _END_ 4


class SeverRequest
{
public:
	std::string method;
	std::string url;
	std::string protocol;
	std::map<std::string, std::string> header_;
	std::string content;
	SOCKET sock;

	SeverRequest() = default;
	~SeverRequest() = default;
	int analysis(SOCKET handle);
	Response* creatResponse();
	void print();
private:
	char input_char = 0;
	int in_methon(SOCKET handle);
	int in_url(SOCKET handle);
	int in_protocol(SOCKET handle);
	int in_Header(SOCKET handle);
	int in_Header_s(SOCKET handle);
	std::string in_Fieldname(SOCKET handle);
	std::string in_id(SOCKET handle);
	int inputcontent(std::string content);

	void urltransfer(std::string& url);
};

#endif // !SEVERREQUEST_H
