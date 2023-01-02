#include <iostream>
#include<string>

#include"SeverSocket.h"
#include"SeverFile.h"





int main() {
	SeverSocket* p=SeverSocket::Get_SeverSocket_Instance();
	system("pause");
	return 0;
}

