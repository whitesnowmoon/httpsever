#ifndef SEVERFILERECV_H
#define SEVERFILERECV_H

#include"SeverFile.h"

class SeverFileRecv :public SeverFile
{
public:
	std::string path="Debug/save/";
	std::string name;
	virtual bool SeverFile_open(std::string name) override;
	virtual bool SeverFile_close() override;
	int SeverFile_recv(std::string content);
	virtual int SeverFile_flush() override;
};

#endif // !SEVERFILERECV_H
