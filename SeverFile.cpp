#include "SeverFile.h"

config* config::SeverConfig = nullptr;
config* config::Get_SeverConfig() {
	static clear clr_SeverConfig;
	if (SeverConfig == nullptr) {
		SeverConfig = new config();
		SeverConfig->load(CONFIG_PATH);
	}
	return SeverConfig;
}

const std::vector<std::pair<std::string, std::string>>& config::Get_Default_Response_Header() {
	return Default_Response_Header;
}

bool config::load(std::string config_path) {
	std::fstream conf;
	conf.open(config_path, std::ios_base::in|std::ios_base::binary);
	if (!conf.is_open()) { 
		std::cout << "config open error\n";
		return _ERROR_; 
	}
	char content[1500]; 
	while (!conf.eof()) {
		std::istream& in = conf.getline(content, sizeof(content));
		std::string temp(content);
		if (temp.find_last_of("\r")!=-1)
			temp.pop_back();
		int flex = temp.find_first_of(':');
		std::string attribute = temp.substr(0, flex);
		std::string id = temp.substr(flex+2, in.gcount());
		std::cout << attribute << id << "\n";
		Default_Response_Header.emplace_back(attribute, id);
	}

}

int Src_File::Src_send(SOCKET dst) {
	file.seekg(0, std::ios_base::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios_base::beg);

	char* buff=new char[this->length];
	file.read(buff, length);
    send(dst, buff, length, 0);
	delete buff;
	
	return 0;
}

bool Src_File::Src_open(std::string url) {
#ifdef DEBUG
	url = "Debug/" + url;
#else
	url.erase(0, 1);
#endif// DEBUG
	  std::cout << "my_url:" << url << "\n";
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

bool Src_File::Src_close() {
	this->file.close();
	if (!file.is_open()) {
		std::cout << "file close\n**********************************************************************************************\n";
		return true;
	}
	return false;
}

