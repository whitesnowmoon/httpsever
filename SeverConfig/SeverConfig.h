#ifndef SEVERCONFIG_H
#define SEVERCONFIG_H


#include<vector>
#include<iostream>
#include"../SeverNet/SocketHandle.h"

class SeverConfig
{
public:
	static std::vector<SocketHandle> listenHandles;
	static std::vector<std::pair<std::string, std::string>> staticheader;
	static std::string CApath;
	static std::string CAkey;
	static std::string password;
	static std::string srcrootpath;
	static std::string openfile;
	static bool init(std::string configpath);
};

#endif // !SEVERCONFIG_H
