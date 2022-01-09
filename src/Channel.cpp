/**
 * @file Channel.cpp
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#include "Channel.h"

#include <unistd.h>

#include <utility>

#include "EventLoop.h"
#include "Socket.h"

const int Channel::kReadEvent = 1;
const int Channel::kWriteEvent = 2;
const int Channel::kET = 4;

Channel::Channel(EventLoop *loop, int fd) : loop_(loop), fd_(fd) {}

Channel::~Channel() {
  loop_->DeleteChannel(this);
  if (fd_ != -1) {
    close(fd_);
  }
}

void Channel::HandleEvent() {
  if (ready_events_ & kReadEvent) {
    read_callback_();
  }
  if (ready_events_ & kWriteEvent) {
    write_callback_();
  }
}

void Channel::EnableRead() {
  listen_events_ |= kReadEvent;
  loop_->UpdateChannel(this);
}

void Channel::EnableWrite() {
  listen_events_ |= kWriteEvent;
  loop_->UpdateChannel(this);
}

void Channel::UseET() {
  listen_events_ |= kET;
  loop_->UpdateChannel(this);
}
int Channel::GetFd() { return fd_; }

int Channel::GetListenEvents() { return listen_events_; }
int Channel::GetReadyEvents() { return ready_events_; }

bool Channel::GetExist() { return exist_; }

void Channel::SetExist(bool in) { exist_ = in; }

void Channel::SetReadyEvents(int ev) {
  if (ev & kReadEvent) {
    ready_events_ |= kReadEvent;
  }
  if (ev & kWriteEvent) {
    ready_events_ |= kWriteEvent;
  }
  if (ev & kET) {
    ready_events_ |= kET;
  }
}

void Channel::SetReadCallback(std::function<void()> const &callback) { read_callback_ = callback; }
void Channel::SetWriteCallback(std::function<void()> const &callback) { write_callback_ = callback; }