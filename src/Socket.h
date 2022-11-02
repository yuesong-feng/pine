#pragma once
#include "common.h"
#include <string>

class Socket {
public:
    DISALLOW_COPY_AND_MOVE(Socket);
    Socket();
    ~Socket();
    void set_fd(int fd);
    int fd();
    std::string get_ip();
    unsigned short get_port();
    RC Create();
    RC Bind();
    RC Listen();
    RC Accept(int &clnt_fd);
    RC Connect(const char*ip, int port);
    RC SetNonBlocking();
    bool IsNonBlocking();
    int RecvBufSize();
private:
    int fd_;
};
