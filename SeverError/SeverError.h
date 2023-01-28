#ifndef SEVERERROR_H
#define SEVERERROR_H

#define _SEVERERROR_QUEUE_SIZE_ 10 //最长错误存储

#include<queue>

enum class SEVERERRORCODE
{
	SEVERUSUALSUCCESS,
	SEVERSOCKETINITERROR,   //socket系统初始化失败
	SEVERGETSOCKETTCPERROR, //获得系统TCPsocket错误
	SEVERADDRESSBINDERROR,   //socket地址绑定错误
	SEVERSOCKETACCEPTERROR,   //socket accept接受出错
	SEVERSOCKETLISTENERROR,     //socket listen监听出错 
	SEVERSOCKETIOCTLSOCKETERROR, //设置socket属性出错
	SEVERCONFIGFILEPATHNOTEXIST,  //config文件路径不存在
	SEVERCONFIGFILEFORMERROR,	//config文件格式错误
	SEVERCONFIGFILEATTRNOTEXIST, //config文件使用了不存在的属性
	SEVERSSLCTXNEWERROR,			//ssl无法创建上下文
	SEVERSSLCERTIFICATEFILEERROR,	//sslCA证书错误
	SEVERSSLPRIVATEKEYFILEERROR,	//ssl 私钥错误
	SEVERSSLPRIVATEKEYINVALID,		//ssl私钥无效
	SEVERSSLPROTOCOLERROR          //网络协议未正常完成
};


class SeverError
{
public:
	static std::queue<SEVERERRORCODE> errorCodeBuff;
	static SEVERERRORCODE GetLastError();
	static void PushError(SEVERERRORCODE code);
};

#endif // !SEVERERROR

