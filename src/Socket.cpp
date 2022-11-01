#include "Socket.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <cassert>

Socket::Socket() : fd_(-1) {}

Socket::~Socket() {
    if (fd_ != -1) {
        close(fd_);
        fd_ = -1;
    }
}

void Socket::set_fd(int fd) { fd_ = fd; }

int Socket::fd() { return fd_; }

RC Socket::Create() {
    assert(fd_ == -1);
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ == -1) {
        perror("Failed to create socket");
        return RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC Socket::Bind() {
    assert(fd_ != -1);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8888);
    if (::bind(fd_, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("Failed to bind socket");
        return RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC Socket::Listen() {
    assert(fd_ != -1);
    if(::listen(fd_, SOMAXCONN) == -1) {
        perror("Failed to listen socket");
        return RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC Socket::Accept(Socket *clnt_sock) {
    assert(fd_ != -1);
    int clnt_fd = ::accept(fd_, NULL, NULL);
    if(clnt_fd == -1) {
        perror("Failed to accept socket");
        return RC_SOCKET_ERROR;
    }
    clnt_sock->set_fd(clnt_fd);
    return RC_SUCCESS;
}

RC Socket::Connect(const char*ip, int port) {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    if (::connect(fd_, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Failed to connect socket");
        return RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}
