#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"

EventLoop::EventLoop() {
    poller_ = std::make_unique<PollPoller>();
}
EventLoop::~EventLoop() {}

void EventLoop::Loop() {
    std::vector<Channel *> active_channels;
    while (poller_->Poll(active_channels) == RC_SUCCESS) {
        for (Channel *ch : active_channels) {
            ch->HandleEvent();
        }
    }
}

RC EventLoop::UpdateChannel(Channel *channel) {
    return poller_->UpdateChannel(channel);
}

RC EventLoop::DeleteChannel(Channel *channel) {
    return poller_->DeleteChannel(channel);
}

