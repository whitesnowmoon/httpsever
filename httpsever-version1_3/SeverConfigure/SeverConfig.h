#ifndef _CONFIG_H
#define _CONFIG_H

#include<iostream>
#include<WinSock2.h>
#include<vector>
#include<fstream>
#pragma comment(lib,"Ws2_32.lib")
#define DEBUG
#ifdef DEBUG
#define CONFIG_PATH "Debug/config.txt"
#else
#define CONFIG_PATH "config.txt"
#endif
#define _ERROR_ -1
class config
{
public:
	static config* Get_SeverConfig();
	const std::vector<std::pair<std::string, std::string>>& Get_Default_Response_Header();
private:
	std::vector<std::pair<std::string, std::string>> Default_Response_Header;
	static config* SeverConfig;
	bool load(std::string config_path);
	class clear
	{
	public:
		~clear() {
			if (SeverConfig)
				delete SeverConfig;
		}
	};
	config() = default;
	~config() = default;
};

#endif // !_CONFIG_H