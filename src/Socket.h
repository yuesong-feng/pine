#pragma once
#include "common.h"

class Socket {
public:
    DISALLOW_COPY_AND_MOVE(Socket);
    Socket();
    ~Socket();
    void set_fd(int fd);
    int fd();
    RC Create();
    RC Bind();
    RC Listen();
    RC Accept(Socket *clnt_sock);
    RC Connect(const char*ip, int port);
private:
    int fd_;
};
