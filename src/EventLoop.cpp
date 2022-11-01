#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"

EventLoop::EventLoop() {
    poller_ = std::make_unique<PollPoller>();
}
EventLoop::~EventLoop() {}

void EventLoop::Loop() {
    while (true) {
        std::vector<Channel *> chs = poller_->Poll();
        for (Channel *ch : chs) {
            ch->handleEvent();
        }
    }
}