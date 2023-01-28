#ifndef SEVERFILELOCAL_H
#define SEVERFILELOCAL_H

#include"SeverFile.h"

class SeverFileLocal :public SeverFile
{
public:
	virtual bool SeverFile_open(std::string path) override;
	virtual int SeverFile_send(SeverAppSocket* handle) override;
	virtual int SeverFile_recv(SeverAppSocket* handle) override;
	virtual int SeverFile_flush() override;
	virtual bool SeverFile_close() override;
};

#endif // !SEVERFILELOCAL_H
