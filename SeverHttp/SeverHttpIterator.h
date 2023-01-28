#ifndef SEVERHTTPITERATOR_H
#define SEVERHTTPITERATOR_H

#include<assert.h>
#include"../SeverNet/SeverApiINet.h"

#define SEVERHTTPITERATOR_ERROR -1

template<typename Chunk>
class SeverHttpIterator
{
public:
	bool IteratorEnd;
	SeverHttpIterator(SeverAppSocket* handle):IteratorEnd(false),handle(handle) {
		if(handle==nullptr)
			assert(handle == nullptr);
	}
	SeverHttpIterator& operator++() {
		if (handle->App_recv(&buff, sizeof(buff)) == SEVERHTTPITERATOR_ERROR) {
			this->IteratorEnd = true;
		}
		return *this;
	}
	SeverHttpIterator& lookAhead() {
		if (handle->App_recv_peek(&buff, sizeof(buff)) == SEVERHTTPITERATOR_ERROR) {
			this->IteratorEnd = true;
		}
		return *this;
	}
	SeverHttpIterator operator++(int) {
		SeverHttpIterator old(*this);
		++(*this);
		return  old;
	}
	operator Chunk*() {
		return &(this->buff);
	}
	operator Chunk() {
		return this->buff;
	}

private:
	SeverAppSocket* handle;
	Chunk buff = '\0';
};

#endif // !SEVERHTTPITERATOR_H



