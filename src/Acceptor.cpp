#include "Acceptor.h"
#include "Socket.h"
#include <cassert>

Acceptor::Acceptor() {
    socket_ = std::make_unique<Socket>();
    assert( socket_->Create() == RC_SUCCESS );
    assert( socket_->Bind() == RC_SUCCESS );
    assert( socket_->Listen() == RC_SUCCESS );
}

Acceptor::~Acceptor() {}

RC Acceptor::Accept() {
    Socket clnt_sock;
    return socket_->Accept(&clnt_sock);
}
