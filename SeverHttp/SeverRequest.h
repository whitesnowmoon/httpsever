#ifndef SEVERREQUEST_H
#define SEVERREQUEST_H

#include<iostream>
#include<map>
#include<string>
#include<vector>
#include"Response.h"
#include"SeverHttpIterator.h"


#define SEVER_REQUEST_OK_ 1
#define SEVER_REQUEST_ERROR_ -1

#define SEVER_REQUEST_ON_ 2
#define SEVER_REQUEST_READLY_ 3
#define SEVER_REQUEST_END_ 4

class Response;
class SeverRequest
{
public:
	std::string method;
	std::string url;
	std::string protocol;
	std::map<std::string, std::string> header_;
	std::string content;
	SeverHttpIterator<char> httpIterator;
	SeverAppSocket* handle;
	SeverRequest(SeverAppSocket* handle);
	~SeverRequest() = default;
	int analysis();
	Response* creatResponse();
	void print();
private:
	char input_char = 0;
	int in_methon();
	int in_url();
	int in_protocol();
	int in_Header();
	int in_Header_s();
	std::string in_Fieldname();
	std::string in_id();
	int inputcontent(std::string content);    //保留

	void urltransfer(std::string& url);  //url分析
	void popspace();                    //去除响应头前一个空格
};

#endif // !SEVERREQUEST_H
