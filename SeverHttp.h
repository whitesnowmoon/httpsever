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
		{"200" ,  "OK"},   //�ͻ�������ɹ�
		{"400" ,  "Bad Request"},   //���ڿͻ����������﷨���󣬲��ܱ�����������⡣
		{"401",   "Unauthonzed"},  //����δ����Ȩ�����״̬��������WWW - Authenticate��ͷ��һ��ʹ��
		{"403",   "Forbidden"},  //�������յ����󣬵��Ǿܾ��ṩ���񡣷�����ͨ��������Ӧ�����и������ṩ�����ԭ��
		{"404",   "Not Found"},  //�������Դ�����ڣ����磬�����˴����URL��
		{"500",   "Internal Server Error"}, //��������������Ԥ�ڵĴ��󣬵����޷���ɿͻ��˵�����
		{"503",   "Service Unavailable"}  //��������ǰ���ܹ�����ͻ��˵�������һ��ʱ��֮�󣬷��������ܻ�ָ�������
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