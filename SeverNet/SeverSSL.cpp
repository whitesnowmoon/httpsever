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
    password.push_back('\0');//\0������ʶ���ս��

    SSL_library_init();// SSL ���ʼ�� 
    OpenSSL_add_all_algorithms();// �����㷨 
    SSL_load_error_strings(); // �������� SSL ������Ϣ 

    ctx = SSL_CTX_new(SSLv23_server_method());//�������ṹ
    if (ctx == NULL) {
        std::cout << "SSL_CTX_new() error";
        SeverError::PushError(SEVERERRORCODE::SEVERSSLCTXNEWERROR);
        return false;
    }
    errorcode = SSL_CTX_use_certificate_file(ctx, CA_file_path.c_str(), SSL_FILETYPE_PEM);//����֤��
    if (errorcode <= 0) {
        std::cout << "SSL_CTX_use_certificate_file() error";
        SeverError::PushError(SEVERERRORCODE::SEVERSSLCERTIFICATEFILEERROR);
        return false;
    }
    SSL_CTX_set_default_passwd_cb_userdata(ctx, (char*)password.c_str());//�����޷����ж�


    errorcode = SSL_CTX_use_PrivateKey_file(ctx, KEY_file_path.c_str(), SSL_FILETYPE_PEM);//����˽Կ
    if (errorcode <= 0) {
        std::cout << "SSL_CTX_use_PrivateKey_file() error";
        SeverError::PushError(SEVERERRORCODE::SEVERSSLPRIVATEKEYFILEERROR);
        return false;
    }
    if (!SSL_CTX_check_private_key(ctx)) {//��֤˽Կ
        std::cout << "SSL_CTX_check_private_key() error";
        SeverError::PushError(SEVERERRORCODE::SEVERSSLPRIVATEKEYINVALID);
        return false;
    }
    return true;
}

SeverSSL::~SeverSSL() {
    SSL_CTX_free(ctx);
}
