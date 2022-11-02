#include "TcpServer.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "Connection.h"
#include "Socket.h"
#include <cassert>

TcpServer::TcpServer() {
    main_reactor_ = std::make_unique<EventLoop>();
    acceptor_ = std::make_unique<Acceptor>(main_reactor_.get());
    std::function<void(int)> cb = std::bind(&TcpServer::NewConnection, this, std::placeholders::_1);
    acceptor_->set_new_connection_callback(cb);
    sub_reactor_ = std::make_unique<EventLoop>();
}

TcpServer::~TcpServer() {}

void TcpServer::Start() {
    main_reactor_->Loop();
}

RC TcpServer::NewConnection(int fd) {
    assert( connections_.find(fd) == connections_.end() );
    std::unique_ptr<Connection> conn = std::make_unique<Connection>(fd, main_reactor_.get());
    std::function<void(int)> del_cb = std::bind(&TcpServer::DeleteConnection, this, std::placeholders::_1);
    conn->set_delete_connection_callback(del_cb);
    conn->set_recv_callback(on_recv_);
    connections_.insert({fd, std::move(conn)});
    if (on_connect_) {
        on_connect_(connections_[fd].get());
    }
    return RC::RC_SUCCESS;
}

RC TcpServer::DeleteConnection(int fd) {
    auto it = connections_.find(fd);
    assert( it != connections_.end() );
    connections_.erase(it);
    return RC_SUCCESS;
}

void TcpServer::onConnect(std::function<void(Connection *)> fn) {
    on_connect_ = std::move(fn);
}

void TcpServer::onRecv(std::function<void(Connection *)> fn) {
    on_recv_ = std::move(fn);
}
