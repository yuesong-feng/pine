#pragma once
#include "common.h"
#include <memory>
#include <functional>
#include <unordered_map>

class TcpServer {
public:
    DISALLOW_COPY_AND_MOVE(TcpServer);
    TcpServer();
    ~TcpServer();
    // start the tcp server
    void Start();
    // create a new connection
    RC NewConnection(int fd);
    // delete a connection
    RC DeleteConnection(int fd);
    // trigger on connect
    void onConnect(std::function<void(Connection *)> fn);
    // trigger on recv
    void onRecv(std::function<void(Connection *)> fn);
private:
    // main reactor for accept new connection
    std::unique_ptr<EventLoop> main_reactor_;
    // to accept new connection
    std::unique_ptr<Acceptor> acceptor_;
    // tcp connections
    std::unordered_map<int, std::unique_ptr<Connection>> connections_;
    // sub reactor for handle connection event
    std::unique_ptr<EventLoop> sub_reactor_;

    // function on connect
    std::function<void(Connection *)> on_connect_;
    // after recv message
    std::function<void(Connection *)> on_recv_;
};
