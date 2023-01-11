#include "Get_SeverResponse.h"

Get_SeverResponse::Get_SeverResponse(SeverRequest* request):request(request),handle(request->sock) {

}


void Get_SeverResponse::loadprotocol(std::string protocol) {
	this->protocol = protocol;
}

SeverFile Get_SeverResponse::loadfile(std::string url) {
	SeverFile src;
	src.SeverFile_open(url);
	return src;
}

void Get_SeverResponse::loadstate_phrase(int cur_state) {
	this->state = Response_States_phrase[cur_state].first;
	this->phrase = Response_States_phrase[cur_state].second;
}

int Get_SeverResponse::loadheader_(std::string url) {
	std::pair<std::string, std::string> module;
	config* c = config::Get_SeverConfig();
	auto vec = c->Get_Default_Response_Header();
	for (int i = 0; i < vec.size(); i++)
	{
		module = vec[i];
		header_.insert(module);
	}
	return 0;
}

void Get_SeverResponse::anwser() {
	Response_combine();
	Response_send(this->handle);
}

void Get_SeverResponse::destroy() {
	delete this;
}

int Get_SeverResponse::Response_send(SOCKET handle) {
	int sum = send(handle, this->Response_header.c_str(), this->Response_header.size(), 0);
	sum += this->content.SeverFile_send(handle);
	this->content.SeverFile_close();
	return sum;
}

int Get_SeverResponse::Response_combine() {

	if (request->url == "/") {
		request->url = "/html/index.html";
	}
	loadprotocol(request->protocol);
	loadheader_(request->url);
	this->content = loadfile(request->url);
	loadstate_phrase(this->content.state);

	if (header_.count("Content-Length")) {
		if (header_["Content-Length"] == "?") {
			header_["Content-Length"] = std::to_string(this->content.length);
		}
	}
	if (header_.count("Content-Type")) {
		if (header_["Content-Type"] == "?") {
			if (Response_Type.count(this->content.type) > 0)
				header_["Content-Type"] = Response_Type[this->content.type];
		}
	}

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
