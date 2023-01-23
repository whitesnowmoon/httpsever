#include "SeverFileRecv.h"

bool SeverFileRecv::SeverFile_open(std::string name) {
	name = this->path + name;
	file.open(name, std::ios_base::in | std::ios_base::binary);
	if (file.is_open()) { return false; }
	file.open(name, std::ios_base::out| std::ios_base::trunc| std::ios_base::binary);
	if (file.is_open())
	{
		return true;
	}
	return false;
}

bool SeverFileRecv::SeverFile_close() {
	file.close();
	return true;
}

int SeverFileRecv::SeverFile_recv(std::string content) {
		file.write(content.c_str(), content.size());
		return file.gcount();
}

int SeverFileRecv::SeverFile_flush() {
	file.flush();
	return file.gcount();
}
