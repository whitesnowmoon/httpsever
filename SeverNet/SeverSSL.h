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
		while (SSL_ERROR_WANT_READ == SSL_get_error(ssl, code))     //�������ȴ��㹻�����ж�Э��
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
	static inline int SSLread(SSL* ssl,char*buff,int len,int flag=0) { //flag����
		return SSL_read(ssl, buff, len);
	}
	static inline int SSLsend(SSL* ssl, char* buff, int len, int flag = 0) {
		return SSL_write(ssl, buff, len);
	}
	static inline int SSLcolse(SSL* ssl) {
		int code = 0;
		if(ERR_get_error()!=0)			//���͹ر�ssl,�����÷��͹���, ��Ȼ������������ܣ������Ǵ��� û��SSL_get_error()�鷳
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
