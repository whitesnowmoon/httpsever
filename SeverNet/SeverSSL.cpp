#include "SeverSSL.h"
#include "../SeverConfig/SeverConfig.h"
#include "../SeverError/SeverError.h"
SeverSSL* SeverSSL::instance = nullptr;
std::atomic<SSL_CTX*> SeverSSL::ctx=nullptr;
SeverSSL* SeverSSL::Get_Instance_SeverSSL() {
    static clear clr_SeverSeverSSL;
    if (instance == nullptr)
        instance = new SeverSSL();
    return instance;
}

bool SeverSSL::_init_() {
    int errorcode;
    std::string CA_file_path = SeverConfig::CApath;
    std::string KEY_file_path = SeverConfig::CAkey;
    std::string password = SeverConfig::password;
    password.push_back('\0');//\0是输入识别终结符

    SSL_library_init();// SSL 库初始化 
    OpenSSL_add_all_algorithms();// 载入算法 
    SSL_load_error_strings(); // 载入所有 SSL 错误消息 

    ctx = SSL_CTX_new(SSLv23_server_method());//创建主结构
    if (ctx == NULL) {
        std::cout << "SSL_CTX_new() error";
        SeverError::PushError(SEVERERRORCODE::SEVERSSLCTXNEWERROR);
        return false;
    }
    errorcode = SSL_CTX_use_certificate_file(ctx, CA_file_path.c_str(), SSL_FILETYPE_PEM);//加载证书
    if (errorcode <= 0) {
        std::cout << "SSL_CTX_use_certificate_file() error";
        SeverError::PushError(SEVERERRORCODE::SEVERSSLCERTIFICATEFILEERROR);
        return false;
    }
    SSL_CTX_set_default_passwd_cb_userdata(ctx, (char*)password.c_str());//函数无返回判断


    errorcode = SSL_CTX_use_PrivateKey_file(ctx, KEY_file_path.c_str(), SSL_FILETYPE_PEM);//加载私钥
    if (errorcode <= 0) {
        std::cout << "SSL_CTX_use_PrivateKey_file() error";
        SeverError::PushError(SEVERERRORCODE::SEVERSSLPRIVATEKEYFILEERROR);
        return false;
    }
    if (!SSL_CTX_check_private_key(ctx)) {//验证私钥
        std::cout << "SSL_CTX_check_private_key() error";
        SeverError::PushError(SEVERERRORCODE::SEVERSSLPRIVATEKEYINVALID);
        return false;
    }
    return true;
}

SeverSSL::~SeverSSL() {
    SSL_CTX_free(ctx);
}
