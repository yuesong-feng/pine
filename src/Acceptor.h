#pragma once
#include "common.h"
#include <memory>
#include <functional>

class Acceptor {
public:
    DISALLOW_COPY_AND_MOVE(Acceptor);
    explicit Acceptor(EventLoop *loop);
    ~Acceptor();
    RC Accept();
    void set_new_connection_callback(std::function<void(int)> fn);
private:
    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

    std::function<void(int)> new_connection_callback_;
};
