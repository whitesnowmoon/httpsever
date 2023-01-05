#include "SeverRequest.h"
#include"Response_Factory.h"
namespace conv
{
	std::string GbkToUtf8(const char* src_str) {
		int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
		std::string strTemp = str;
		if (wstr) delete[] wstr;
		if (str) delete[] str;
		return strTemp;
	}
	std::string Utf8ToGbk(const char* src_str) {
		int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
		wchar_t* wszGBK = new wchar_t[len + 1];
		memset(wszGBK, 0, len * 2 + 2);
		MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
		len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
		char* szGBK = new char[len + 1];
		memset(szGBK, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
		std::string strTemp(szGBK);
		if (wszGBK) delete[] wszGBK;
		if (szGBK) delete[] szGBK;
		return strTemp;
	}
}
int SeverRequest::analysis(SOCKET handle) {
	this->sock = handle;
	recv(handle, &input_char, 1, 0);
	if (in_methon(handle) == _ERROR_)return _ERROR_;
	if (in_url(handle) == _ERROR_)return _ERROR_;
	if (in_protocol(handle) == _ERROR_)return _ERROR_;
	if (in_Header(handle) == _ERROR_)return _ERROR_;
	if (input_char == 0x0D)
	{
		recv(handle, &input_char, 1, 0);
		if (input_char == 0x0A) {
			urltransfer(this->url);
			return _OK_;
		}
		else
		{
			return _ERROR_;
		}
	}
	return _ERROR_;
}

Response* SeverRequest::creatResponse() {
	Response_Factory factory; Response* response=nullptr;
	if(this->method=="GET")
		response = factory.CreatResponse(module_name::GET,this);
	return response;
}

void SeverRequest::print() {
	std::cout << "method:" << method << "\n";
	std::cout << "url:" << url << "\n";
	std::cout << "protocol:" << protocol << "\n";
	for (auto iter = header_.rbegin(); iter != header_.rend(); iter++) {
		std::cout << iter->first << " " << iter->second << std::endl;
	}
}

int SeverRequest::in_methon(SOCKET handle) {
	int state = _ON_, times = 0;
	while (state != _END_)
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

int SeverRequest::in_url(SOCKET handle) {
	int state = _ON_, times = 0;
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

int SeverRequest::in_protocol(SOCKET handle) {
	int state = _ON_, times = 0;
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

std::string SeverRequest::in_Fieldname(SOCKET handle) {
	int state = _ON_, times = 0; std::string buff;
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

std::string SeverRequest::in_id(SOCKET handle) {
	int state = _ON_, times = 0; std::string buff;
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

void SeverRequest::urltransfer(std::string& url) {
	if (url.size() == 0)return;
	int index = 0;
	index = url.find('%', index);
	while (index != std::string::npos)
	{
		unsigned char c = 0, t = 0;
		for (size_t i = 1; i <= 2; i++)
		{
			t = url[index + i];
			if (t <= '9' && t >= '0') {
				t = t - '0';
			}
			else if (t <= 'F' && t >= 'A') {
				t = t - 'A' + 10;
			}
			else {
				std::cout << "url transfer error\n";
			}
			c += (t << ((2 - i) * 4));
		}
		std::string replace_;
		replace_.push_back(c);
		url.replace(index, 3, replace_);
		index = url.find('%', index);
	}
	url = conv::Utf8ToGbk(url.c_str());
}

int SeverRequest::in_Header(SOCKET handle) {
	if (in_Header_s(handle) == _ERROR_)
		return _ERROR_;
	return _OK_;
}

int SeverRequest::in_Header_s(SOCKET handle) {
	int state = _ON_;
	if (input_char == 0x0D)
	{
		state = _READLY_;
		char tempc = 0;
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
		if (input_char == 0x20) {
			recv(handle, &input_char, 1, 0);
		}
		std::string key_word = in_Fieldname(handle);
		if (key_word.size() > 1000)return _ERROR_;
		std::string key_id = in_id(handle);
		if (key_id.size() > 1000)return _ERROR_;
		header_.emplace(key_word, key_id);
		if (in_Header(handle) == _ERROR_)return _ERROR_;
		return _OK_;
	}
}