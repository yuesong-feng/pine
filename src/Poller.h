#pragma once
#include "common.h"
#include <memory>
#include <poll.h>
#include <vector>
#include <unordered_map>
class Channel;

class Poller {
public:
    DISALLOW_COPY_AND_MOVE(Poller);
    Poller() = default;
    virtual ~Poller() = default;
    virtual RC Add(Channel *channel) = 0;
    virtual std::vector<Channel *> Poll() = 0;
protected:
    std::unordered_map<int, Channel *> channel_map_;
};

class PollPoller : public Poller{
public:
    DISALLOW_COPY_AND_MOVE(PollPoller);
    PollPoller();
    ~PollPoller();
    RC Add(Channel *channel) override;
    std::vector<Channel *> Poll() override;
private:
    std::vector<struct pollfd> pfds_;
};