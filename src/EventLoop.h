#pragma once
#include "common.h"
#include <memory>

class EventLoop {
public:
    DISALLOW_COPY_AND_MOVE(EventLoop);
    EventLoop();
    ~EventLoop();
    void Loop();
    RC UpdateChannel(Channel *channel);
    RC DeleteChannel(Channel *channel);
private:
    std::unique_ptr<Poller> poller_;
};
