#pragma once
#include "common.h"
#include <memory>
#include <functional>
#include <string>

class Connection {
public:
    DISALLOW_COPY_AND_MOVE(Connection);
    Connection(int fd, EventLoop *loop);
    ~Connection();
    std::unique_ptr<Socket> &socket();
    const std::string &recv_buf() const;
    void set_send_buf(std::string send_buf);
    void set_delete_connection_callback(std::function<void(int)> fn);
    void set_recv_callback(std::function<void(Connection *)> fn);
    RC Recv();
    RC Send();
private:
    RC RecvBlocking();
    RC RecvNonBlocking();
    RC SendBlocking();
    RC SendNonBlocking();
    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
    
    std::string recv_buf_;
    std::string send_buf_;

    std::function<void(int)> delete_connection_callback_;
    std::function<void(Connection *)> recv_callback_;
};