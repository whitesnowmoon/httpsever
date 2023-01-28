
#include <iostream>
#include<fstream>
#include"SeverNet/SeverApiINet.h"
#include"SeverHttp/SeverRequest.h"
#include"SeverSrc/SeverFileLocal.h"
#include"SeverConfig/SeverConfig.h"
//int htc(SeverAppSocket* handle) {
//    char buff[2048];
//    memset(buff, '\0', 2048);
//    int nRecv = handle->App_recv(buff, 1024);
//    std::cout << nRecv << "\n" << buff<<"\n";
//
//    /*
//    SeverRequest Request_tool;
//    Request_tool.analysis(this->cur_socket);
//	Response* response =Request_tool.creatResponse();
//	response->anwser();
//	response->destroy();
//    */
//    std::fstream file;
//    file.open("D:/web/d.html");
//    file.seekg(0, std::ios_base::end);
//    std::streampos fileSize = file.tellg();
//    file.seekg(0, std::ios_base::beg);
//    char* buff_ = new char[fileSize];
//    file.read(buff_, fileSize);
//    std::string header = "HTTP/1.1 200 OK\r\n\r\n";
//    header.append(buff_, fileSize);
//    //nRecv = send(handle->clientSocket,(char*)header.c_str(), header.size(),0);
//    nRecv=handle->App_send((char*)header.c_str(), header.size());
//    int e = WSAGetLastError();
//    std::cout << nRecv << "\n" << header << "\n";
//    return 0;
//}
int htc(SeverAppSocket* handle) {
    SeverRequest request(handle);
    request.analysis();
    //request.print();
    Response * response=request.creatResponse();
    response->anwser();
    response->destroy();
    //SeverFileLocal file;
    //file.SeverFile_open("D:/web/d.html");
    //file.SeverFile_send(handle);
    //file.SeverFile_close();
    //std::cout << file.name << " " << file.length << " " << file.state << "\n";
    //char buff[2048];
    //memset(buff, '\0', 2048);
    //int nRecv = handle->App_recv(buff, 1024);
    //std::cout <<"recv"<< nRecv << "\n" << buff << "\n";
    //std::fstream file;
    //file.open("D:/web/d.html");
    //file.seekg(0, std::ios_base::end);
    //std::streampos fileSize = file.tellg();
    //file.seekg(0, std::ios_base::beg);
    //char* buff_ = new char[fileSize];
    //file.read(buff_, fileSize);
    //std::string header = "HTTP/1.1 200 OK\r\n\r\n";
    //header.append(buff_, fileSize);
    //nRecv=handle->App_send((char*)header.c_str(), header.size());
    //std::cout << "send" << nRecv << "\n" << buff << "\n";
    return 0;
}

int main()
{

    SeverConfig::init("Debug/config.txt");
    SeverApiNet a;
    a._run_(htc);
    system("pause");
    return 0;
}

