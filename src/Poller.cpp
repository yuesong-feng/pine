#include "Poller.h"
#include "Channel.h"

PollPoller::PollPoller() {}

PollPoller::~PollPoller() {}

RC PollPoller::UpdateChannel(Channel *channel) {
    auto it = channel_map_.find(channel->fd());
    if (it == channel_map_.end()) {
        struct pollfd pfd;
        pfd.fd = channel->fd();
        pfd.events = 0;
        pfd.revents = 0;

        short events = channel->events();
        if (events & Channel::EVENT_READ) {
            pfd.events |= POLLIN;
        }
        if (events & Channel::EVENT_WRITE) {
            pfd.events |= POLLOUT;
        }

        pfds_.push_back(std::move(pfd));
        channel_map_[channel->fd()] = channel;
    } else {
        return RC_UNIMPLEMENTED;
    }
    return RC_SUCCESS;
}

RC PollPoller::DeleteChannel(Channel *channel) {
    auto ch_it = channel_map_.find(channel->fd());
    assert( ch_it != channel_map_.end() );
    int fd = ch_it->second->fd();
    for (auto it = pfds_.begin(); it != pfds_.end(); ++it) {
        if (it->fd == fd) {
            pfds_.erase(it);
            break;
        }
    }
    channel_map_.erase(ch_it);
    return RC_SUCCESS;
}

RC PollPoller::Poll(std::vector<Channel *> &active_channels) {
    active_channels.clear();
    int ready = ::poll(&*pfds_.begin(), pfds_.size(), -1);
    if (ready == 0) {
        return RC_SUCCESS;
    } else if(ready == -1) {
        return RC_POLLER_ERROR;
    }
    for (auto &pfd : pfds_) {
        if (pfd.revents > 0) {
            assert(channel_map_.find(pfd.fd) != channel_map_.end());
            Channel *ch = channel_map_[pfd.fd];
            if (pfd.revents & POLLIN) {
                ch->set_revents(Channel::EVENT_READ);
            }
            if (pfd.revents & POLLOUT) {
                ch->set_revents(Channel::EVENT_WRITE);
            }
            active_channels.push_back(ch);
        }
    }
    return RC_SUCCESS;
}