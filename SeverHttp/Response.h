#ifndef _RESPONSE_H
#define _RESPONSE_H

#include<iostream>
#include<map>
#include<string>
#include<vector>
#include"SeverRequest.h"
#include"../SeverSrc/SeverFileLocal.h"
class SeverRequest;
enum class module_name
{
	GET,
	POST
};
class Response
{
public:
	SeverRequest* request;
	virtual void anwser() = 0;
	virtual void destroy() = 0;
	virtual ~Response();
	void addheader_(std::pair<std::string, std::string> module);
	int Response_send(SeverAppSocket* handle);
	int Response_combine();
	Response(SeverRequest* request);
	std::string Response_header;
	std::string protocol;
	std::string state;
	std::string phrase;
	std::map<std::string, std::string> header_;
	SeverFileLocal* src;
	void loadprotocol(std::string& protocol);
	bool loadfile(std::string& url);
	void loadstate_phrase(std::string state);
	int loadheader_(std::string url);
	std::map<std::string, std::string> Response_States_phrase
	{
		{"200" ,  "OK"},   //客户端请求成功
		{"400" ,  "Bad Request"},   //由于客户端请求有语法错误，不能被服务器所理解。
		{"401",   "Unauthonzed"},  //请求未经授权。这个状态代码必须和WWW - Authenticate报头域一起使用
		{"403",   "Forbidden"},  //服务器收到请求，但是拒绝提供服务。服务器通常会在响应正文中给出不提供服务的原因
		{"404",   "Not Found"},  //请求的资源不存在，例如，输入了错误的URL。
		{"500",   "Internal Server Error"}, //服务器发生不可预期的错误，导致无法完成客户端的请求。
		{"503",   "Service Unavailable"},  //服务器当前不能够处理客户端的请求，在一段时间之后，服务器可能会恢复正常。
		{"206",   "partical content"}
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
#endif // !_RESPONSE_H

