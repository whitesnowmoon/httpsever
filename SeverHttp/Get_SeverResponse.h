#ifndef GET_SEVERRESPONSE_H
#define GET_SEVERRESPONSE_H

#include<iostream>
#include<map>
#include<string>
#include<vector>
#include"SeverRequest.h"
#include"Response.h"
#include"../SeverSrc/SeverFileLocal.h"

class Get_SeverResponse :public Response
{
public:
	virtual void anwser() override;
	virtual void destroy() override;
	Get_SeverResponse(SeverRequest* request);
	~Get_SeverResponse();
private:
	SeverRequest* request;
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
		{"200" ,  "OK"},   //�ͻ�������ɹ�
		{"400" ,  "Bad Request"},   //���ڿͻ����������﷨���󣬲��ܱ�����������⡣
		{"401",   "Unauthonzed"},  //����δ����Ȩ�����״̬��������WWW - Authenticate��ͷ��һ��ʹ��
		{"403",   "Forbidden"},  //�������յ����󣬵��Ǿܾ��ṩ���񡣷�����ͨ��������Ӧ�����и������ṩ�����ԭ��
		{"404",   "Not Found"},  //�������Դ�����ڣ����磬�����˴����URL��
		{"500",   "Internal Server Error"}, //��������������Ԥ�ڵĴ��󣬵����޷���ɿͻ��˵�����
		{"503",   "Service Unavailable"},  //��������ǰ���ܹ�����ͻ��˵�������һ��ʱ��֮�󣬷��������ܻ�ָ�������
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
	int Response_send(SeverAppSocket* handle);
	int Response_combine();
};

#endif // !GET_SEVERRESPONSE_H