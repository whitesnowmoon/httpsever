#include "SeverSSL.h"
#include <openssl/err.h>


int my_cb(char* buf, int size, int rwflag, void* u) {
    static char password[16] = "liguoliang1848\0";
    memcpy(buf, (char*)password, 16);
    buf[size - 1] = '\0';
    return 16;
}


SeverSSL* SeverSSL::instance = nullptr;
SeverSSL* SeverSSL::Get_Instance_SeverSSL() {
    static clear clr_SeverSSL;
    if (instance == nullptr)
        instance = new SeverSSL();
    return instance;
}

SSL_Handle SeverSSL::CreatSSL_Handle(SOCKET sock, SSL_FUN fun) {
    return SSL_Handle(sock,fun,ctx);
}

SeverSSL::SeverSSL() {
     int errorcode;
    std::string CA_file_path="Debug/Moon_CA_SEVER.crt";
    std::string KEY_file_path = "Debug/Moon_CA_SEVER.key";

    SSL_library_init();// SSL 库初始化 
    OpenSSL_add_all_algorithms();// 载入算法 
    SSL_load_error_strings(); // 载入所有 SSL 错误消息 
 
    ctx = SSL_CTX_new(SSLv23_server_method());//创建主结构
    if (ctx == NULL) {
        std::cout << "SSL_CTX_new() error";
        exit(1);
    }
    errorcode = SSL_CTX_use_certificate_file(ctx, CA_file_path.c_str(), SSL_FILETYPE_PEM);//加载证书
    if (errorcode <= 0) {
        std::cout << "SSL_CTX_use_certificate_file() error";
        exit(1);
    }

    //pem_password_cb* fun = nullptr;
    SSL_CTX_set_default_passwd_cb(ctx, my_cb);
    std::string password = "liguoliang1848\0";
    //char password[16] = "liguoliang1848\0";
    //SSL_CTX_set_default_passwd_cb_userdata(ctx, password);


    errorcode = SSL_CTX_use_PrivateKey_file(ctx, KEY_file_path.c_str(), SSL_FILETYPE_PEM);//加载私钥
    if (errorcode <= 0) {
        std::cout << "SSL_CTX_use_PrivateKey_file() error";
        exit(1);
    }
    if (!SSL_CTX_check_private_key(ctx)) {//验证私钥
        std::cout << "SSL_CTX_check_private_key() error";
        exit(1);
    }
}

SeverSSL::~SeverSSL() {
    SSL_CTX_free(ctx);
}


SSL_Handle::SSL_Handle(SSL_Handle&& old) :ctx(ctx), fun(fun) {
}

SSL_Handle::SSL_Handle(const SSL_Handle& old) :ctx(ctx), fun(fun) {
}

SSL_Handle::SSL_Handle(SOCKET sock, SSL_FUN fun, SSL_CTX* ctx):ctx(ctx),fun(fun) {
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);//绑定
}

int SSL_Handle::run() {
    ERR_clear_error();
    int error = SSL_accept(ssl);
    if (error<=0) {
        long e = 1;
        while (e)
        {
            e = ERR_get_error();
            char eee[1024];
            memset(eee, '\0', 1024);
            char* g=ERR_error_string(e, eee);
            if(g)
            printf("%s\n", g);
        }
       // std::cout << "SSL_accept error "<<SSL_get_error(ssl,error)<<"\n";

        return -1;
    }
    std::cout << "success\n";
    return this->fun(ssl);
}

SSL_Handle::~SSL_Handle() {
    /* 关闭 SSL 连接 */
        SSL_shutdown(ssl);
        SSL_free(ssl);
}
