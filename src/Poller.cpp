#include "Poller.h"
#include "Channel.h"

PollPoller::PollPoller() {}

PollPoller::~PollPoller() {}

RC PollPoller::Add(Channel *channel) {
    if (channel_map_.find(channel->fd()) != channel_map_.end()) {
        return RC_SUCCESS;
    }
    struct pollfd pfd;
    pfd.fd = channel->fd();
    pfd.events = channel->events();
    pfd.revents = 0;
    pfds_.push_back(std::move(pfd));
    channel_map_[channel->fd()] = channel;
    return RC_SUCCESS;
}

std::vector<Channel *> PollPoller::Poll() {
    int ready = ::poll(&*pfds_.begin(), pfds_.size(), -1);
    if (ready == 0) {
        return {};
    } else if(ready == -1) {
        return {};
    }
    std::vector<Channel *> active_fds;
    for (auto &pfd : pfds_) {
        if (pfd.revents > 0) {
            assert(channel_map_.find(pfd.fd) != channel_map_.end());
            active_fds.push_back(channel_map_[pfd.fd]);
        }
    }
    return active_fds;
}