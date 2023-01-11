#ifndef _RESPONSE_H
#define _RESPONSE_H
enum class module_name
{
	GET,
	POST
};
class Response
{
public:
	virtual void anwser() = 0;
	virtual void destroy() = 0;
};
#endif // !_RESPONSE_H

