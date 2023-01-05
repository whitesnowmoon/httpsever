#include "SeverConfig.h"
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
	conf.open(config_path, std::ios_base::in | std::ios_base::binary);
	if (!conf.is_open()) {
		std::cout << "config open error\n";
		return _ERROR_;
	}
	char content[1500];
	while (!conf.eof()) {
		std::istream& in = conf.getline(content, sizeof(content));
		std::string temp(content);
		if (temp.find_last_of("\r") != -1)
			temp.pop_back();
		int flex = temp.find_first_of(':');
		std::string attribute = temp.substr(0, flex);
		std::string id = temp.substr(flex + 2, in.gcount());
		Default_Response_Header.emplace_back(attribute, id);
	}
}