#include "Channel.h"
#include "EventLoop.h"
#include <cassert>

const short Channel::EVENT_READ = 1;
const short Channel::EVENT_WRITE = 4;

Channel::Channel(int fd, EventLoop *loop) : fd_(fd), loop_(loop), events_(0), revents_(0) {}

Channel::~Channel() {
    assert( loop_->DeleteChannel(this) );
}

int Channel::fd() { return fd_; }

short Channel::events() { return events_; }

short Channel::revents() { return revents_;  }

void Channel::set_revents(short revents) { revents_ |= revents; }

void Channel::set_read_callback(std::function<void()> read_callback) { read_callback_ = std::move(read_callback); }

void Channel::HandleEvent() {
    if (read_callback_ && (revents_ & EVENT_READ)) {
        read_callback_();
    }
}

RC Channel::EnableRead() {
    events_ |= EVENT_READ;
    return loop_->UpdateChannel(this);
}
