#include "Get_SeverResponse.h"
#include "../SeverConfig/SeverConfig.h"
Get_SeverResponse::Get_SeverResponse(SeverRequest* request):Response(request){
	this->src = nullptr;
}

Get_SeverResponse::~Get_SeverResponse() {

}

void Get_SeverResponse::anwser() {
	if (this->request->header_["Cookie"] != "123456") {   //Cookie¹ýÂË
		loadfile(SeverConfig::openfile);
	}
	Response_combine();
	Response_send(this->request->handle);
}

void Get_SeverResponse::destroy() {
	delete this;
}


