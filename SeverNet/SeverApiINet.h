#ifndef SEVERAPINET_H
#define SEVERAPINET_H

#include "SeverSocketOpen.h"
#include "../SeverConfig/SeverConfig.h"

class SeverApiNet
{
public:
	int _run_(Callback_Funtion htc) {
        SeverSSL::Get_Instance_SeverSSL()->_init_();
        if (!SeverSocketOpen::Get_SeverSocket_Instance()->_init_(SeverConfig::listenHandles)) {
            std::cout << "init error\n";
            return -1;
        }
        SeverSocketOpen::Get_SeverSocket_Instance()->setCallback(htc);
        SeverSocketOpen::Get_SeverSocket_Instance()->run();
        if (SeverError::errorCodeBuff.size()) {
            std::cout << "error:" << (int)SeverError::errorCodeBuff.front();
        }
	}
};


#endif // !SEVERAPINET_H

