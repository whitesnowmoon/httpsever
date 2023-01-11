#ifndef POST_SEVERRESPONSE_H
#define POST_SEVERRESPONSE_H

#include"Response.h"
#include"SeverRequest.h"

#define _ERROR_ -1
enum class  post_Content_Type_num
{
	not_exist_error=-1,
	application_x_www_form_urlencoded = 1,
	application_json,
	multipart_form_data
};
class Post_SeverResponse :public Response
{
public:
	virtual void anwser() override;
	virtual void destroy() override;
	Post_SeverResponse(SeverRequest* request);
	~Post_SeverResponse() = default;
private:
	SeverRequest* request;
	unsigned int Length;
	std::string ContentType;
	post_Content_Type_num analysis_post_Content_Type();
	int get_multipart_form_data();
	int application_x_www_form_urlencoded(std::string& content);
	std::map<std::string, post_Content_Type_num> post_Content_Type{
		{"application/x-www-form-urlencoded",post_Content_Type_num::application_x_www_form_urlencoded},
		{"application/json",post_Content_Type_num::application_json},
		{"multipart/form-data",post_Content_Type_num::multipart_form_data}
	};
};
#endif // !1


