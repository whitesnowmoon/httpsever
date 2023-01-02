#ifndef SEVERFILE_H
#define SEVERFILE_H
#include<iostream>
#include<WinSock2.h>
#include<vector>
#include<fstream>
#pragma comment(lib,"Ws2_32.lib")
//#define DEBUG
#ifdef DEBUG
#define CONFIG_PATH "Debug/config.txt"
#else
#define CONFIG_PATH "config.txt"
#endif
#define _ERROR_ -1

class Src_File
{
public:
	virtual int Src_send(SOCKET dst);
	virtual bool Src_open(std::string url);
	virtual bool Src_close();
	virtual int Src_recv(SOCKET src) { return 0; }
	virtual int Src_flush() { return 0; }
	int length;	
	std::string type;
	int state;
private:
	std::fstream file;
};
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
	config()=default;
	~config()=default;
};


class SeverFile
{
	std::string Sever_System_Path;
	
};

#endif 