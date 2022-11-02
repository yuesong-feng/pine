#pragma once
#include "common.h"
#include <memory>
#include <functional>

class Channel {
public:
    DISALLOW_COPY_AND_MOVE(Channel);
    Channel(int fd, EventLoop *loop);
    ~Channel();
    int fd();
    short events();
    short revents();
    void set_revents(short revents);
    void set_read_callback(std::function<void()> read_callback);
    void HandleEvent();
    RC EnableRead();
    static const short EVENT_READ;
    static const short EVENT_WRITE;
private:
    int fd_;
    EventLoop *loop_;
    short events_;
    short revents_;

    std::function<void()> read_callback_;
};