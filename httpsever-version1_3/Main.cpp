#include"SeverNet/SeverSocketOpen.h"
int main() {
	SeverSocketOpen* p = SeverSocketOpen::Get_SeverSocket_Instance();
	p->run();
	system("pause");
	return 0;
}