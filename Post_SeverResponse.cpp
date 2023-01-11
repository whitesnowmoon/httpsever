#include "Post_SeverResponse.h"
#include "SeverFileRecv.h"
void Post_SeverResponse::anwser() {
	std::string content;
	post_Content_Type_num type=analysis_post_Content_Type();
	if (type == post_Content_Type_num::multipart_form_data) {
		get_multipart_form_data();//ÎÄ¼þ
	}
	if (type == post_Content_Type_num::application_x_www_form_urlencoded) {
		application_x_www_form_urlencoded(content);//×Ö·û´®
	}
	SeverFile send_file;
	if(this->request->url=="/")
		this->request->url = "/html/index.html";
	send_file.SeverFile_open(this->request->url);
	send_file.SeverFile_send(this->request->sock);
	send_file.SeverFile_close();
	std::cout<<"\*************/\n" << content << "\n";
}

void Post_SeverResponse::destroy() {
	delete this;
}

Post_SeverResponse::Post_SeverResponse(SeverRequest* request):request(request){

}

post_Content_Type_num Post_SeverResponse::analysis_post_Content_Type() {
	this->request->print();
	this->Length=std::atoll(this->request->header_["Content-Length"].c_str());
	this->ContentType = this->request->header_["Content-Type"];
	for (auto i = post_Content_Type.begin(); i!= post_Content_Type.end(); i++)
	{
		int c = ContentType.find(i->first);
		if (c== 1) {
			return i->second;
		}
	}
	return post_Content_Type_num::not_exist_error;

}

int Post_SeverResponse::get_multipart_form_data() {
	std::string temp = "boundary=----";
	int index = this->ContentType.find(temp);
	std::string boundary = "------";
	boundary += this->ContentType.substr(index + temp.size());
	unsigned int sum = 0,error=0;
	if (this->Length > 1024000000) {

	}
	char* content_temp = new char[this->Length];
	while (sum!=this->Length)
	{
		int recv_t=recv(this->request->sock, content_temp, 65536, 0);
		if (recv_t < 0) { error++; }
		else{
			sum += recv_t;
		}
		if (error > 1024000000|| sum > this->Length)return _ERROR_;

	}
	std::string content_temp_,content;
	content_temp_.append(content_temp, this->Length);
	int f_index = content_temp_.find("\r\n\r\n");
	int l_index = content_temp_.find(boundary, f_index+4);
	content = content_temp_.substr(f_index + 4, l_index- (f_index+4+2));
	delete[] content_temp;
	SeverFileRecv file;
	file.SeverFile_open("temp.html");
	file.SeverFile_recv(content);
	file.SeverFile_close();
	return sum;
}

int Post_SeverResponse::application_x_www_form_urlencoded(std::string& content) {
	unsigned int sum = 0, error = 0;
	if (this->Length > 1024000000) {

	}
	char* content_temp = new char[this->Length];
	while (sum != this->Length)
	{
		int recv_t = recv(this->request->sock, content_temp, 65536, 0);
		if (recv_t < 0) { error++; }
		else {
			sum += recv_t;
		}
		if (error > 1024000000 || sum > this->Length)return _ERROR_;

	}
	content.clear();
	content.append(content_temp, this->Length);
	delete[] content_temp;
	return sum;
}
