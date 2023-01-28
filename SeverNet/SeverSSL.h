#ifndef SEVERSSL_H
#define SEVERSSL_H

#include<openssl/ssl.h>
#include<openssl/err.h>
#include<iostream>
#include<atomic>
#include"../SeverError/SeverError.h"

class SeverSSL
{
public:
	static SeverSSL* Get_Instance_SeverSSL();
	bool _init_();
	static inline int SSLaccept(SSL* ssl) {
		int code = SSL_accept(ssl);
		while (SSL_ERROR_WANT_READ == SSL_get_error(ssl, code))     //非阻塞等待足够报文判断协议
		{
			code = SSL_accept(ssl);
		}
		if (code<0) {
			SeverError::PushError(SEVERERRORCODE::SEVERSSLPROTOCOLERROR);
		}else{
			ERR_clear_error();
		}
		return code;
	}
	static inline int SSLread(SSL* ssl,char*buff,int len,int flag=0) { //flag对齐
		return SSL_read(ssl, buff, len);
	}
	static inline int SSLsend(SSL* ssl, char* buff, int len, int flag = 0) {
		return SSL_write(ssl, buff, len);
	}
	static inline int SSLcolse(SSL* ssl) {
		int code = 0;
		if(ERR_get_error()!=0)			//发送关闭ssl,错误不用发送过程, 虽然有其他错误可能，但还是错误 没用SSL_get_error()麻烦
			code=SSL_shutdown(ssl);
		SSL_free(ssl);
		return code;
	}
	static std::atomic<SSL_CTX*> ctx;
private:
	class clear
	{
	public:
		~clear() {
			if (instance)
				delete instance;
		}
	};
	SeverSSL() = default;
	~SeverSSL();
	static SeverSSL* instance;
};

#endif // !SEVERSSL_H
