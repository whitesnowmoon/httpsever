#ifndef SEVERSSL_H
#define SEVERSSL_H

#include<openssl/ssl.h>
#include<WinSock2.h>
#include<iostream>

typedef int (*SSL_FUN)(SSL* ssl);
class SeverSSL;
class SSL_Handle
{
	friend class SeverSSL;
public:
	int run();
	SSL_Handle(SSL_Handle&& old);
	SSL_Handle(const SSL_Handle& old);
	SSL_Handle(SOCKET sock, SSL_FUN fun, SSL_CTX* ctx);
	~SSL_Handle();
private:
	bool end = 0;
	SSL_CTX* ctx;
	SSL_FUN fun;
	SSL* ssl;
};


class SeverSSL
{
public:
	SSL_CTX* ctx;
	static SeverSSL* instance;
	static SeverSSL* Get_Instance_SeverSSL();
	SSL_Handle CreatSSL_Handle(SOCKET sock, SSL_FUN fun);

	SeverSSL();
	~SeverSSL();
	class clear
	{
	public:
		~clear() {
			if (instance)
				delete instance;
		}
	};
private:

};

#endif // !SEVERSSL_H
