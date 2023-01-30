#include "Post_SeverResponse.h"
#include "../SeverSrc/SeverFileLocal.h"
void Post_SeverResponse::anwser() {
	std::string content;
	post_Content_Type_num type=analysis_post_Content_Type();
	if (type == post_Content_Type_num::application_x_www_form_urlencoded) {
		application_x_www_form_urlencoded(content);//×Ö·û´®
		std::vector<std::pair<std::string, std::string>> form=Getkeyword(content);
		if (form[1].second == "123456") {  //ÃÜÂë
			std::pair<std::string, std::string> module;
			module.first = "Set-Cookie";
			module.second = "123456; Path=/";
			addheader_(module);
		}
		else
		{
			loadfile(SeverConfig::openfile);
		}
		Response_combine();
		Response_send(this->request->handle);
	}
	else
	{
		char buff[10240];
		request->handle->App_recv(buff, 10240);
	}
	std::cout<<"\*************/\n" << content << "\n\*******************************\\\n";
}

void Post_SeverResponse::destroy() {
	delete this;
}

Post_SeverResponse::Post_SeverResponse(SeverRequest* request):Response(request){
	this->Length = 0;
}

post_Content_Type_num Post_SeverResponse::analysis_post_Content_Type() {
	this->request->print();
	this->Length=std::atoll(this->request->header_["Content-Length"].c_str());
	this->ContentType = this->request->header_["Content-Type"];
	for (auto i = post_Content_Type.begin(); i!= post_Content_Type.end(); i++)
	{
		int c = ContentType.find(i->first);
		if (c== 0) {
			return i->second;
		}
	}
	return post_Content_Type_num::not_exist_error;

}


std::vector<std::pair<std::string, std::string>> Post_SeverResponse::Getkeyword(std::string& url) {
	std::vector<std::pair<std::string, std::string>> form;
	int index = 0; int flex = 0; int start = 0;
	while (true)
	{
		flex = url.find('=', flex);
		index=url.find('&', index);
		form.emplace_back(url.substr(start, flex - start), url.substr(flex+1, index - flex-1));
		if (index == -1)break;
		start = (++index);
		flex++;

	}
	return form;
}

int Post_SeverResponse::application_x_www_form_urlencoded(std::string& content) {
	unsigned int sum = 0, error = 0;
	if (this->Length > 1024000000) {
		
	}
	char* content_temp = new char[this->Length];
	while (sum != this->Length)
	{
		int recv_t = this->request->handle->App_recv(content_temp, 65536);
		if (recv_t < 0) { error++; }
		else {
			sum += recv_t;
		}
		if (error > 1024000000 || sum > this->Length)return _ERROR_;

	}
	content.clear();
	content.append(content_temp, this->Length);
	delete[] content_temp;
	return sum;
}
