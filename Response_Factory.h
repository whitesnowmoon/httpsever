#pragma once
#ifndef RESPONSE_FACTORY_H
#define RESPONSE_FACTORY_H

#include"Response.h"
#include"Get_SeverResponse.h"
#include"SeverRequest.h"

class Response_Factory
{
public:
	Response* CreatResponse(module_name name, SeverRequest* request);
};
#endif // !RESPONSE_FACTORY_H

