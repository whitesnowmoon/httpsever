<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio">
<TITLE></TITLE>
</HEAD>
<BODY>
	���Ƿ�����������ӿ�ģ��

	��νṹ(����һ���Ǽ̳�ʵ��,������ϵ)
	{
		int htc()
		SeverSocketOpen->SeverThreadPool{
			->SeverHttpHandle->(whether SeverAppSocket turn sock | ssl)->htc(SeverAppSocket)
			->SeverHttpHandle
			->SeverHttpHandle
		}
	}

	{
		winsock->SeverSocket->|						  |->AppSockHandle
					SeverSSL->|---->SeverAppSocket--->|->AppSSLHandle
		SeverAppSocket.ssl_init()->AppSSLHandle//��������ʹ��
	}

	{
		SocketHandle->SocketApp->SeverAppSocket
	}
	
	ִ�����ÿһ�߳���Ҫʹ��SeverAppSocket���ڴ����ݽṹ,
	ÿһ�߳�����accept���պ󣬷���delete��new SeverAppSocket����������ʹ�ã�
	Ĭ����ͨ��ָ�봫��,�����²��ʹ�������շ�ͨ��SeverAppSocket*��

	SeverSocket.h 
		�Եײ����ϵͳ����ӿڷ�װ����ʵ�ֲ�ͬ����ϵͳ���ݣ�
	������һЩ�������͵ļ򻯣�ת����

	SocketHandle.h
		����ӿڵײ����ݽṹ��������ַ���˿ڣ��Ѿ��Զ������ǵ�
	�������ͣ��ͼ���SEVERSOCKET

	SocketApp.h
		����Ӧ�ò����ݽṹ�������շ�����ʱ�䣬�����С,�ͻ�
	��SEVERSOCKET��

	SeverSSL.h
		��openssl���г�ʼ���ӿڷ�װ��

	SeverSocketOpen.h
		��������ӿڣ���ʼ���ӿ��̣߳�ҵ��ʵ�ֻص�������ʼ��
	�ص����������̰߳�ȫ��

	SeverHttpHandle.h
		httpҵ��ӿڣ�����ÿ���߳��д�����ʹ��ҵ��ص�����

	SeverAppSocket.h
		����ssl�ṹ
		http�����ӿڣ���װ��ssl�Լ�ԭʼ�׽����շ����� 
	���Ե���ssl_init_Ҳ���Բ�ʹ�ã���Ϊ���������麯���ķ���
	��ʼ���˲�һ��ʹ�á�

	AppSSLHandle.h
		ssl�շ�
	AppSockHandle.h
	   ԭʼ�׽����շ�
	SeverApiINet.h
		SeverNet��ȫ����װ
</BODY>
</HTML>
