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

};

#endif // !GET_SEVERRESPONSE_H