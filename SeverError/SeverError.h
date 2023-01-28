#ifndef SEVERERROR_H
#define SEVERERROR_H

#define _SEVERERROR_QUEUE_SIZE_ 10 //�����洢

#include<queue>

enum class SEVERERRORCODE
{
	SEVERUSUALSUCCESS,
	SEVERSOCKETINITERROR,   //socketϵͳ��ʼ��ʧ��
	SEVERGETSOCKETTCPERROR, //���ϵͳTCPsocket����
	SEVERADDRESSBINDERROR,   //socket��ַ�󶨴���
	SEVERSOCKETACCEPTERROR,   //socket accept���ܳ���
	SEVERSOCKETLISTENERROR,     //socket listen�������� 
	SEVERSOCKETIOCTLSOCKETERROR, //����socket���Գ���
	SEVERCONFIGFILEPATHNOTEXIST,  //config�ļ�·��������
	SEVERCONFIGFILEFORMERROR,	//config�ļ���ʽ����
	SEVERCONFIGFILEATTRNOTEXIST, //config�ļ�ʹ���˲����ڵ�����
	SEVERSSLCTXNEWERROR,			//ssl�޷�����������
	SEVERSSLCERTIFICATEFILEERROR,	//sslCA֤�����
	SEVERSSLPRIVATEKEYFILEERROR,	//ssl ˽Կ����
	SEVERSSLPRIVATEKEYINVALID,		//ssl˽Կ��Ч
	SEVERSSLPROTOCOLERROR          //����Э��δ�������
};


class SeverError
{
public:
	static std::queue<SEVERERRORCODE> errorCodeBuff;
	static SEVERERRORCODE GetLastError();
	static void PushError(SEVERERRORCODE code);
};

#endif // !SEVERERROR

