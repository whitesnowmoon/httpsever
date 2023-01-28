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
	std::string rootPath;                   //��·����Ĭ�����
	int length;                        //�����������  �ļ�����
	std::string name;					//����������� �ļ�����
	bool state;							//�����������	�ļ�״̬ ��/�ر�
public:
	std::fstream file;
};
#endif

