#include "Channel.h"

Channel::Channel() {}

Channel::~Channel() {}

int Channel::fd() { return fd_; }

short Channel::events() { return events_; }

void Channel::handleEvent() {}