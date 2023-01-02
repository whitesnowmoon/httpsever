#pragma once
#ifndef SEVERHTTP_H
#define SEVERHTTP_H

#include<iostream>
#include<WinSock2.h>
#include<map>
#include<string>
#include<vector>
#include"SeverFile.h"
#pragma comment(lib,"Ws2_32.lib")
#define _OK_ 1
#define _ERROR_ -1



class Request
{
public:
	std::string method;
	std::string url;
	std::string protocol;
	std::map<std::string, std::string> header_;
	std::string content;
	int Integrity;
	Request()=default;
	~Request() = default;
	int analysis(SOCKET handle);
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
class Response
{
public:
	int Response_send(SOCKET handle);
	int Response_combine(Request request);
	Response() = default;
	~Response() = default;
private:
	std::string Response_header;
	std::string protocol;
	std::string state;
	std::string phrase;
	std::map<std::string, std::string> header_;
	Src_File content;
	void loadprotocol(std::string protocol);
	Src_File  loadfile(std::string url);
	void loadstate_phrase(int cur_state);
	int loadheader_(std::string url);
	std::vector<std::pair<std::string, std::string>> Response_States_phrase
	{
		{"200" ,  "OK"},   //客户端请求成功
		{"400" ,  "Bad Request"},   //由于客户端请求有语法错误，不能被服务器所理解。
		{"401",   "Unauthonzed"},  //请求未经授权。这个状态代码必须和WWW - Authenticate报头域一起使用
		{"403",   "Forbidden"},  //服务器收到请求，但是拒绝提供服务。服务器通常会在响应正文中给出不提供服务的原因
		{"404",   "Not Found"},  //请求的资源不存在，例如，输入了错误的URL。
		{"500",   "Internal Server Error"}, //服务器发生不可预期的错误，导致无法完成客户端的请求。
		{"503",   "Service Unavailable"}  //服务器当前不能够处理客户端的请求，在一段时间之后，服务器可能会恢复正常。
	};
	std::map<std::string, std::string> Response_Type
	{
		{".html","text/html"},
		{".jpg","image/jpeg"},
		{".png","image/png"},
		{".css","text/css"},
		{".js","application/x-javascript"}
	};
};



class SeverHttp
{
private:
	Request request;
	Response response;
	SOCKET sock;
public:
	SeverHttp(SOCKET sock) {
		this->sock = sock;
	}
	void run() {
		request.analysis(sock);
		response.Response_combine(request);
		response.Response_send(sock);
	}
};

#endif 