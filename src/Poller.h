#pragma once
#include "common.h"
#include <memory>
#include <poll.h>
#include <vector>
#include <unordered_map>

class Poller {
public:
    DISALLOW_COPY_AND_MOVE(Poller);
    Poller() = default;
    virtual ~Poller() = default;
    virtual RC UpdateChannel(Channel *channel) = 0;
    virtual RC DeleteChannel(Channel *channel) = 0;
    virtual RC Poll(std::vector<Channel *> &active_channels) = 0;
protected:
    std::unordered_map<int, Channel *> channel_map_;
};

class PollPoller : public Poller{
public:
    DISALLOW_COPY_AND_MOVE(PollPoller);
    PollPoller();
    ~PollPoller();
    RC UpdateChannel(Channel *channel) override;
    RC DeleteChannel(Channel *channel) override;
    RC Poll(std::vector<Channel *> &active_channels) override;
private:
    std::vector<struct pollfd> pfds_;
};