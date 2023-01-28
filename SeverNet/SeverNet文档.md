<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio">
<TITLE></TITLE>
</HEAD>
<BODY>
	这是服务器的网络接口模块

	层次结构(不是一定是继承实现,描述关系)
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
		SeverAppSocket.ssl_init()->AppSSLHandle//提升必须使用
	}

	{
		SocketHandle->SocketApp->SeverAppSocket
	}
	
	执行完毕每一线程主要使用SeverAppSocket的内存数据结构,
	每一线程阻塞accept接收后，反复delete和new SeverAppSocket传给其他包使用，
	默认是通过指针传递,所有下层包使用网络收发通过SeverAppSocket*。

	SeverSocket.h 
		对底层操作系统网络接口封装，以实现不同操作系统兼容，
	并进行一些数据类型的简化，转换。

	SocketHandle.h
		网络接口底层数据结构，包括地址，端口，已经自定义它们的
	服务类型，和监听SEVERSOCKET

	SocketApp.h
		网络应用层数据结构，包括收发阻塞时间，缓冲大小,客户
	端SEVERSOCKET。

	SeverSSL.h
		对openssl进行初始化接口封装。

	SeverSocketOpen.h
		开启网络接口，初始化接口线程，业务实现回调函数初始化
	回调函数必须线程安全。

	SeverHttpHandle.h
		http业务接口，会在每个线程中创建并使用业务回调函数

	SeverAppSocket.h
		具有ssl结构
		http网络层接口，封装了ssl以及原始套接字收发功能 
	可以调用ssl_init_也可以不使用，因为子类会进行虚函数的分类
	初始化了不一定使用。

	AppSSLHandle.h
		ssl收发
	AppSockHandle.h
	   原始套接字收发
	SeverApiINet.h
		SeverNet包全部封装
</BODY>
</HTML>
