#include "Acceptor.h"
#include "Socket.h"
#include "EventLoop.h"
#include "Channel.h"
#include <cassert>

Acceptor::Acceptor(EventLoop *loop) {
    socket_ = std::make_unique<Socket>();
    assert( socket_->Create() == RC_SUCCESS );
    assert( socket_->Bind() == RC_SUCCESS );
    assert( socket_->Listen() == RC_SUCCESS );
    channel_ = std::make_unique<Channel>(socket_->fd(), loop);
    std::function<void()> cb = std::bind(&Acceptor::Accept, this);
    channel_->set_read_callback(cb);
    assert( channel_->EnableRead() == RC_SUCCESS );
}

Acceptor::~Acceptor() {}

RC Acceptor::Accept() {
    int clnt_sock = -1;
    assert( socket_->Accept(clnt_sock) == RC_SUCCESS );
    if (new_connection_callback_) {
        new_connection_callback_(clnt_sock);
    }
    return RC_SUCCESS;
}

void Acceptor::set_new_connection_callback(std::function<void(int)> fn) {
    new_connection_callback_ = std::move(fn);
}