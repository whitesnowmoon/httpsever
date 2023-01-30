#include "SeverRequest.h"
#include"Response_Factory.h"

namespace conv
{
#ifdef _SEVER_WIN_
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
#endif // _SEVER_WIN_


}
SeverRequest::SeverRequest(SeverAppSocket* handle):httpIterator(handle),handle(handle){
}
int SeverRequest::analysis() {
	input_char=++httpIterator;
	if (in_methon() == SEVER_REQUEST_ERROR_)return SEVER_REQUEST_ERROR_;
	if (in_url() == SEVER_REQUEST_ERROR_)return SEVER_REQUEST_ERROR_;
	if (in_protocol() == SEVER_REQUEST_ERROR_)return SEVER_REQUEST_ERROR_;
	if (in_Header() == SEVER_REQUEST_ERROR_)return SEVER_REQUEST_ERROR_;
	if (input_char == 0x0D)
	{
		input_char = ++httpIterator;
		if (input_char == 0x0A) {
			urltransfer(this->url);
			popspace();
			return SEVER_REQUEST_OK_;
		}
		else
		{
			return SEVER_REQUEST_ERROR_;
		}
	}
	return SEVER_REQUEST_ERROR_;
}

Response* SeverRequest::creatResponse() {
	Response_Factory factory; Response* response=nullptr;
	if(this->method=="GET")
		response = factory.CreatResponse(module_name::GET,this);
	if (this->method == "POST")
		response = factory.CreatResponse(module_name::POST, this);
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

int SeverRequest::in_methon() {
	int state = SEVER_REQUEST_ON_, times = 0;
	while (state != SEVER_REQUEST_END_)
	{
		if (input_char == 0x20) {
			state = SEVER_REQUEST_END_;
			input_char = ++httpIterator;
		}
		else
		{
			method.push_back(input_char);
			input_char = ++httpIterator;
			times++; if (times > 100)return SEVER_REQUEST_ERROR_;
		}
	}
	return SEVER_REQUEST_OK_;
}

int SeverRequest::in_url() {
	int state = SEVER_REQUEST_ON_, times = 0;
	while (state != SEVER_REQUEST_END_)
	{
		if (input_char == 0x20) {
			state = SEVER_REQUEST_END_;
			input_char = ++httpIterator;
		}
		else
		{
			url.push_back(input_char);
			input_char = ++httpIterator;
			times++; if (times > 1000)return SEVER_REQUEST_ERROR_;
		}
	}
	return SEVER_REQUEST_OK_;
}

int SeverRequest::in_protocol() {
	int state = SEVER_REQUEST_ON_, times = 0;
	while (state != SEVER_REQUEST_END_)
	{
		if (input_char == 0x0D) {
			state = SEVER_REQUEST_READLY_;
			input_char = ++httpIterator;
		}
		else if (input_char == 0x0A && state == SEVER_REQUEST_READLY_) {
			state = SEVER_REQUEST_END_;
			input_char = ++httpIterator;
		}
		else
		{
			state = SEVER_REQUEST_ON_;
			protocol.push_back(input_char);
			input_char = ++httpIterator;
			times++; if (times > 50)return SEVER_REQUEST_ERROR_;
		}
	}
	return SEVER_REQUEST_OK_;
}

std::string SeverRequest::in_Fieldname() {
	int state = SEVER_REQUEST_ON_, times = 0; std::string buff;
	while (state != SEVER_REQUEST_END_)
	{
		if (input_char == 0x3A) {
			state = SEVER_REQUEST_END_;
			input_char = ++httpIterator;
		}
		else
		{
			state = SEVER_REQUEST_ON_;
			buff.push_back(input_char);
			input_char = ++httpIterator;
			times++; if (times > 1000)return buff;
		}
	}
	return buff;
}

std::string SeverRequest::in_id() {
	int state = SEVER_REQUEST_ON_, times = 0; std::string buff;
	while (state != SEVER_REQUEST_END_)
	{
		if (input_char == 0x0D) {
			state = SEVER_REQUEST_READLY_;
			input_char = ++httpIterator;
		}
		else if (input_char == 0x0A && state == SEVER_REQUEST_READLY_) {
			state = SEVER_REQUEST_END_;
			input_char = ++httpIterator;
		}
		else
		{
			state = SEVER_REQUEST_ON_;
			buff.push_back(input_char);
			input_char = ++httpIterator;
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
	}//将转义字符去除
	{
		//额外参数处理?key1=value1&key2=value2
	}
	url = conv::Utf8ToGbk(url.c_str());//适配电脑字符
}

void SeverRequest::popspace() {
	for (auto pos = header_.begin(); pos != header_.end(); pos++) {
		pos->second.erase(0,1);
	}
}

int SeverRequest::in_Header() {
	if (in_Header_s() == SEVER_REQUEST_ERROR_)
		return SEVER_REQUEST_ERROR_;
	return SEVER_REQUEST_OK_;
}

int SeverRequest::in_Header_s() {
	int state = SEVER_REQUEST_ON_;
	if (input_char == 0x0D)
	{
		state = SEVER_REQUEST_READLY_;
		char tempc = 0;
		tempc = httpIterator.lookAhead();
		if (tempc == 0x0A && state == SEVER_REQUEST_READLY_) {
			state = SEVER_REQUEST_END_;
			return SEVER_REQUEST_OK_;
		}
		else
		{
			return SEVER_REQUEST_ERROR_;
		}
	}
	else
	{
		if (input_char == 0x20) {
			input_char = ++httpIterator;
		}
		std::string key_word = in_Fieldname();
		if (key_word.size() > 1000)return SEVER_REQUEST_ERROR_;
		std::string key_id = in_id();
		if (key_id.size() > 1000)return SEVER_REQUEST_ERROR_;
		header_.emplace(key_word, key_id);
		if (in_Header() == SEVER_REQUEST_ERROR_)return SEVER_REQUEST_ERROR_;
		return SEVER_REQUEST_OK_;
	}
}