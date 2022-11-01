#pragma once
#include "common.h"
#include <memory>

class EventLoop;
class Acceptor;

class TcpServer {
DISALLOW_COPY_AND_MOVE(TcpServer);
public:
    TcpServer();
    ~TcpServer();
    void Start();
private:
    std::unique_ptr<EventLoop> main_reactor_;
    std::unique_ptr<Acceptor> acceptor_;
};
