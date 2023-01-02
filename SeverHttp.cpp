#include "SeverHttp.h"
#include"SeverConv.h"
#define _ON_ 0
#define _READLY_ 1
#define _END_ 2

int Request::analysis(SOCKET handle) {
	recv(handle, &input_char, 1, 0);
	if(in_methon(handle) ==_ERROR_)return _ERROR_;
	if(in_url(handle) == _ERROR_)return _ERROR_;
	if (in_protocol(handle) == _ERROR_)return _ERROR_;
	if (in_Header(handle) == _ERROR_)return _ERROR_;
	if (input_char == 0x0D)
	{
		recv(handle, &input_char, 1, 0);
		if (input_char == 0x0A) {
			urltransfer(this->url);
			print();
			return _OK_;
		}
		else
		{
			return _ERROR_;
		}
	}
	return _ERROR_;
}

void Request::print() {
	std::cout << "method:" << method << "\n";
	std::cout << "url:" << url << "\n";
	std::cout << "protocol:" << protocol << "\n";
	for (auto iter = header_.rbegin(); iter != header_.rend(); iter++) {
		std::cout << iter->first << " " << iter->second << std::endl;
	}
}

int Request::in_methon(SOCKET handle) {
	int state = _ON_,times=0;
	while (state!=_END_)
	{
		if (input_char == 0x20) { 
			state = _END_;
		    recv(handle, &input_char, 1, 0);
		}
		else
		{
			method.push_back(input_char);
			recv(handle, &input_char, 1, 0);
			times++; if (times > 100)return _ERROR_;
		}
	}
	return _OK_;
}

int Request::in_url(SOCKET handle) {
	int state = _ON_,times=0; 
	while (state != _END_)
	{
		if (input_char == 0x20) {
			state = _END_;
			recv(handle, &input_char, 1, 0);
		}
		else
		{
			url.push_back(input_char);
			recv(handle, &input_char, 1, 0);
			times++; if (times > 1000)return _ERROR_;
		}
	}
	return _OK_;
}

int Request::in_protocol(SOCKET handle) {
	int state = _ON_, times=0;
	while (state != _END_)
	{
		if (input_char == 0x0D) {
			state = _READLY_;
			recv(handle, &input_char, 1, 0);
		}
		else if (input_char == 0x0A && state == _READLY_) {
			state = _END_; 
			recv(handle, &input_char, 1, 0);
		}
		else
		{
			state = _ON_;
			protocol.push_back(input_char);
			recv(handle, &input_char, 1, 0);
			times++; if (times > 50)return _ERROR_;
		}
	}
	return _OK_;
}

std::string Request::in_Fieldname(SOCKET handle) {
	int state = _ON_, times=0; std::string buff;
	while (state != _END_)
	{
		if (input_char == 0x3A) {
			state = _END_;
			recv(handle, &input_char, 1, 0);
		}
		else
		{
			state = _ON_;
			buff.push_back(input_char);
			recv(handle, &input_char, 1, 0);
			times++; if (times > 1000)return buff;
		}
	}
	return buff;
}

std::string Request::in_id(SOCKET handle) {
    int state = _ON_, times=0; std::string buff;
	while (state != _END_)
	{
		if (input_char == 0x0D) {
			state = _READLY_;
			recv(handle, &input_char, 1, 0);
		}
		else if (input_char == 0x0A && state == _READLY_) {
			state = _END_;
			recv(handle, &input_char, 1, 0);
		}
		else
		{
			state = _ON_;
			buff.push_back(input_char);
			recv(handle, &input_char, 1, 0);
			times++; if (times > 1000)return buff;
		}
	}
	return buff;
}

void Request::urltransfer(std::string& url) {
	if (url.size()==0)return;
	int index = 0;
	index = url.find('%', index);
	while (index!= std::string::npos)
	{
		unsigned char c=0,t=0;
		for (size_t i = 1; i <= 2; i++)
		{
			t = url[index+i];
			if (t <= '9' && t >= '0') {
				t = t - '0';
			}
			else if (t <= 'F' && t >= 'A') {
				t = t - 'A' + 10;
			}
			else {
				std::cout << "url transfer error\n";
			}
			c += (t << ((2-i) * 4));
		}
		std::string replace_;
		replace_.push_back(c);
		url.replace(index, 3, replace_);
		index = url.find('%', index);
	}
	url=conv::Utf8ToGbk(url.c_str());
}

int Request::in_Header(SOCKET handle) {
	if (in_Header_s(handle) == _ERROR_)
		return _ERROR_;
	return _OK_;
}

int Request::in_Header_s(SOCKET handle) {
	int state = _ON_;
	if (input_char == 0x0D)
	{
		state = _READLY_;
		char tempc=0;
		recv(handle, &tempc, 1, MSG_PEEK);
		if (tempc == 0x0A && state == _READLY_) {
			state = _END_;
			return _OK_;
		}
		else
		{
			return _ERROR_;
		}
	}
	else
	{
		if (input_char == 0x20){
			recv(handle, &input_char, 1, 0);
		}
		std::string key_word = in_Fieldname(handle);
		if (key_word.size()> 1000)return _ERROR_;
		std::string key_id = in_id(handle);
		if (key_id.size() > 1000)return _ERROR_;
		header_.emplace(key_word, key_id);
		if (in_Header(handle) == _ERROR_)return _ERROR_;
		return _OK_;
	}
}

void Response::loadprotocol(std::string protocol) {
	this->protocol = protocol;
}

Src_File Response::loadfile(std::string url) {
	Src_File src;
	src.Src_open(url);
	return src;
}

void Response::loadstate_phrase(int cur_state) {
	this->state = Response_States_phrase[cur_state].first;
	this->phrase = Response_States_phrase[cur_state].second;
}

int Response::loadheader_(std::string url) {
	std::pair<std::string, std::string> module;
	config* c=config::Get_SeverConfig();
	auto vec=c->Get_Default_Response_Header();
	for (int i = 0; i < vec.size(); i++)
	{
		module = vec[i];
		header_.insert(module);
	}
	return 0;
}

int Response::Response_send(SOCKET handle) {
	int sum =send(handle, this->Response_header.c_str(), this->Response_header.size(), 0);
	sum += this->content.Src_send(handle);
	this->content.Src_close();
	return sum;
}

int Response::Response_combine(Request request) {

	if (request.url == "/") {
		request.url = "/html/index.html";
	}
	loadprotocol(request.protocol);
	loadheader_(request.url);
	this->content = loadfile(request.url);
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
	for (auto i =header_.begin(); i != header_.end(); i++)
	{
		Response_header += i->first;
		Response_header += ": ";
		Response_header += i->second;
		Response_header += "\r\n";
	}
	Response_header += "\r\n";
	std::cout <<"\n" << Response_header;
	return Response_header.size();
}

