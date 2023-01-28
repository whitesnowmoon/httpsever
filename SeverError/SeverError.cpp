#include "SeverError.h"
#include<mutex>

std::queue<SEVERERRORCODE> SeverError::errorCodeBuff;
SEVERERRORCODE SeverError::GetLastError() {
	return SeverError::errorCodeBuff.back();
}

void SeverError::PushError(SEVERERRORCODE code) {
	static std::mutex errorInGuard;
	if (errorCodeBuff.size() >= _SEVERERROR_QUEUE_SIZE_) {
		errorCodeBuff.pop();
	}
	else
	{
		std::unique_lock<std::mutex> g(errorInGuard);
		errorCodeBuff.push(code);                 //多线程使指针越界
	}
}
