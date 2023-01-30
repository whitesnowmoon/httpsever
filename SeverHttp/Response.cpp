#include "Response.h"

void Response::loadprotocol(std::string& protocol) {
	this->protocol = protocol;
}

bool Response::loadfile(std::string& url) {
	if(this->src!=nullptr)
		return true;
	this->src = new SeverFileLocal();
	if (src->SeverFile_open(url))
		return true;
	return false;
}

void Response::loadstate_phrase(std::string state) {
	this->state = state;
	this->phrase = Response_States_phrase[state];
}


int Response::loadheader_(std::string url) {
	std::pair<std::string, std::string> module;

	auto vec = SeverConfig::staticheader;
	for (int i = 0; i < vec.size(); i++)
	{
		module = vec[i];
		header_.insert(module);
	}
	if (this->src->state) {
		if (header_.count("Content-Length")) {
			if (header_["Content-Length"] == "?") {
				header_["Content-Length"] = std::to_string(this->src->length);
			}
		}
		if (header_.count("Content-Type")) {
			if (header_["Content-Type"] == "?") {
				if (Response_Type.count(this->src->name.substr(this->src->name.find_last_of("."))) > 0)
					header_["Content-Type"] = Response_Type[this->src->name.substr(this->src->name.find_last_of("."))];
			}
		}
	}
	return 0;
}

Response::~Response() {
	if (src) {
		src->SeverFile_close();
		delete src;
		src = nullptr;
	}
}

void Response::addheader_(std::pair<std::string, std::string> module) {
	header_.insert(module);
}
int Response::Response_send(SeverAppSocket* handle) {
	int sum = handle->App_send((char*)this->Response_header.c_str(), this->Response_header.size());
	sum += this->src->SeverFile_send(handle);
	return sum;
}

int Response::Response_combine() {

	if (request->url == "/") {
		request->url = SeverConfig::openfile;
	}
	if (loadfile(request->url)) {
		loadstate_phrase("200");
	}
	else
	{
		loadstate_phrase("404");
	}
	loadprotocol(request->protocol);
	loadheader_(request->url);

	Response_header += this->protocol;
	Response_header += " ";
	Response_header += this->state;
	Response_header += " ";
	Response_header += this->phrase;
	Response_header += "\r\n";
	for (auto i = header_.begin(); i != header_.end(); i++)
	{
		Response_header += i->first;
		Response_header += ": ";
		Response_header += i->second;
		Response_header += "\r\n";
	}
	Response_header += "\r\n";
	//std::cout <<"\n" << Response_header;
	return Response_header.size();
}


Response::Response(SeverRequest* request):request(request) {
	this->src = nullptr;
}
