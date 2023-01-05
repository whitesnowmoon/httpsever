#include "SeverFile.h"
int SeverFile::SeverFile_send(SOCKET dst) {
	file.seekg(0, std::ios_base::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios_base::beg);
	char* buff = new char[this->length];
	file.read(buff, length);
	send(dst, buff, length, 0);
	delete buff;

	return 0;
}

bool SeverFile::SeverFile_open(std::string url) {
#ifdef DEBUG
	url = "Debug/" + url;
#else
	url.erase(0, 1);
#endif// DEBUG
	std::cout << "my_url:" << url << "           end" << "\n";
	file.open(url, std::ios_base::in | std::ios_base::binary);
	if (file.is_open())
	{
		file.seekg(0, std::ios_base::end);
		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios_base::beg);
		this->length = fileSize;
		this->type = url.substr(url.find_last_of("."));
		this->state = 0;
		return true;
	}
	this->state = 4;
	return false;
}

bool SeverFile::SeverFile_close() {
	this->file.close();
	if (!file.is_open()) {
		//std::cout << "file close\n**********************************************************************************************\n";
		return true;
	}
	return false;
}

