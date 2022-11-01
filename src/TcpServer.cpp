#include "TcpServer.h"
#include "EventLoop.h"
#include "Acceptor.h"

TcpServer::TcpServer() {
    main_reactor_ = std::make_unique<EventLoop>();
    acceptor_ = std::make_unique<Acceptor>();
}

TcpServer::~TcpServer() {}

void TcpServer::Start() {
    main_reactor_->Loop();
}
