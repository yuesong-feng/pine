#pragma once
#include "common.h"
#include <memory>
class Poller;

class EventLoop {
DISALLOW_COPY_AND_MOVE(EventLoop);
public:
    EventLoop();
    ~EventLoop();
    void Loop();
private:
    std::unique_ptr<Poller> poller_;
};