#include "SeverFileLocal.h"
#include"../SeverConfig/SeverConfig.h"

//std::string SeverFileLocal::rootPath = SeverConfig::srcrootpath; 不可以
//std::string SeverFileLocal::rootPath(SeverConfig::srcrootpath);  同不可以,因为静态对象在程序开始就初始化了，不等加载所以都是null
bool SeverFileLocal::SeverFile_open(std::string path) {
	rootPath = SeverConfig::srcrootpath;
	std::string localpath =rootPath+path;
	std::cout << localpath << "\n";
	file.open(localpath, std::ios_base::in | std::ios_base::binary);
	if (file.is_open())
	{
		file.seekg(0, std::ios_base::end);
		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios_base::beg);
		this->length = fileSize;
		unsigned int index1 = localpath.find_last_of("/");
		unsigned int index2 = localpath.find_last_of("\\");
		this->name = localpath.substr(index1< index2 ? index1: index2);
		this->state = true;
		return true;
	}
	this->state = false;
	return false;
}

int SeverFileLocal::SeverFile_send(SeverAppSocket* handle) {
	int num = 0;
	if (this->state == true) {
		file.seekg(0, std::ios_base::end);
		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios_base::beg);
		char* buff = new char[this->length];
		file.read(buff, length);
		int num = handle->App_send(buff, length);
		delete buff;
	}
	else
	{
		return -1;
	}
	if (num == length);
		return num;
	return -1;
}

int SeverFileLocal::SeverFile_recv(SeverAppSocket* handle) {
	return 0;
}

int SeverFileLocal::SeverFile_flush() {
	return 0;
}

bool SeverFileLocal::SeverFile_close() {
	this->state = false;
	this->file.close();
	if (!file.is_open()) {
		return true;
	}
	return false;
}
