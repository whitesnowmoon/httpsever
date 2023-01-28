#ifndef SEVERFILE_H
#define SEVERFILE_H
#include<iostream>
#include<vector>
#include<fstream>
#include"../SeverNet/SeverApiINet.h"

class SeverFile
{
public:
	virtual bool SeverFile_open(std::string path) = 0;
	virtual int SeverFile_send(SeverAppSocket* handle)=0;
	virtual int SeverFile_recv(SeverAppSocket* handle) = 0;
	virtual int SeverFile_flush()=0;
	virtual bool SeverFile_close() = 0;
	std::string rootPath;                   //根路径可默认相对
	int length;                        //必须填充属性  文件长度
	std::string name;					//必须填充属性 文件名字
	bool state;							//必须填充属性	文件状态 打开/关闭
public:
	std::fstream file;
};
#endif

