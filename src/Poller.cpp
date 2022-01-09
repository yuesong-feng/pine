/**
 * @file Poller.cpp
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#include "Poller.h"

#include <unistd.h>

#include <cstring>

#include "Channel.h"
#include "util.h"
#define MAX_EVENTS 1000

#ifdef OS_LINUX

Poller::Poller() {
  fd_ = epoll_create1(0);
  ErrorIf(fd_ == -1, "epoll create error");
  events_ = new epoll_event[MAX_EVENTS];
  memset(events_, 0, sizeof(*events_) * MAX_EVENTS);
}

Poller::~Poller() {
  if (fd_ != -1) {
    close(fd_);
  }
  delete[] events_;
}

std::vector<Channel *> Poller::Poll(int timeout) {
  std::vector<Channel *> active_channels;
  int nfds = epoll_wait(fd_, events_, MAX_EVENTS, timeout);
  ErrorIf(nfds == -1, "epoll wait error");
  for (int i = 0; i < nfds; ++i) {
    Channel *ch = (Channel *)events_[i].data.ptr;
    int events = events_[i].events;
    if (events & EPOLLIN) {
      ch->SetReadyEvents(ch->kReadEvent);
    }
    if (events & EPOLLOUT) {
      ch->SetReadyEvents(ch->kWriteEvent);
    }
    if (events & EPOLLET) {
      ch->SetReadyEvents(ch->kET);
    }
    active_channels.push_back(ch);
  }
  return active_channels;
}

void Poller::UpdateChannel(Channel *ch) {
  int fd = ch->GetFd();
  struct epoll_event ev {};
  ev.data.ptr = ch;
  if (ch->GetListenEvents() & ch->kReadEvent) {
    ev.events |= EPOLLIN | EPOLLPRI;
  }
  if (ch->GetListenEvents() & ch->kWriteEvent) {
    ev.events |= EPOLLOUT;
  }
  if (ch->GetListenEvents() & ch->kET) {
    ev.events |= EPOLLET;
  }
  if (!ch->GetExist()) {
    ErrorIf(epoll_ctl(fd_, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add error");
    ch->SetExist();
  } else {
    ErrorIf(epoll_ctl(fd_, EPOLL_CTL_MOD, fd, &ev) == -1, "epoll modify error");
  }
}

void Poller::DeleteChannel(Channel *ch) {
  int fd = ch->GetFd();
  ErrorIf(epoll_ctl(fd_, EPOLL_CTL_DEL, fd, nullptr) == -1, "epoll delete error");
  ch->SetExist(false);
}
#endif

#ifdef OS_MACOS

Poller::Poller() {
  fd_ = kqueue();
  ErrorIf(fd_ == -1, "kqueue create error");
}

Poller::~Poller() {
  if (fd_ != -1) {
    close(fd_);
  }
}

std::vector<Channel *> Poller::Poll(int timeout) {
  std::vector<Channel *> active_channels;
  struct timespec ts;
  ts.tv_sec = timeout / 1000;
  ts.tv_nsec = (timeout % 1000) * 1000 * 1000;
  struct kevent active_events[MAX_EVENTS];
  int n = kevent(fd_, NULL, 0, active_events, MAX_EVENTS, &ts);
  for (int i = 0; i < n; ++i) {
    Channel *ch = (Channel *)active_events[i].udata;
    int events = active_events[i].filter;
    if (events & EVFILT_READ) {
      ch->SetReadyEvents(ch->kReadEvent | ch->kET);
    }
    if (events & EVFILT_WRITE) {
      ch->SetReadyEvents(ch->kWriteEvent | ch->kET);
    }
    active_channels.push_back(ch);
  }
  return active_channels;
}

void Poller::UpdateChannel(Channel *ch) {
  struct kevent ev[2];
  int n = 0;
  int fd = ch->GetFd();
  if (ch->GetListenEvents() & ch->kReadEvent) {
    EV_SET(&ev[n++], fd, EVFILT_READ, EV_ADD | EV_ENABLE | EV_CLEAR, 0, 0, (void *)ch);
  }
  if (ch->GetListenEvents() & ch->kWriteEvent) {
    EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_ADD | EV_ENABLE | EV_CLEAR, 0, 0, (void *)ch);
  }
  int r = kevent(fd_, ev, n, NULL, 0, NULL);
  ErrorIf(r == -1, "kqueue add event error");
}

void Poller::DeleteChannel(Channel *ch) {
  struct kevent ev[2];
  int n = 0;
  int fd = ch->GetFd();
  if (ch->GetListenEvents() & ch->kReadEvent) {
    EV_SET(&ev[n++], fd, EVFILT_READ, EV_DELETE, 0, 0, (void *)ch);
  }
  if (ch->GetListenEvents() & ch->kWriteEvent) {
    EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_DELETE, 0, 0, (void *)ch);
  }
  int r = kevent(fd_, ev, n, NULL, 0, NULL);
  ErrorIf(r == -1, "kqueue delete event error");
}
#endif
