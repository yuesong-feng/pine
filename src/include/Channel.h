/**
 * @file Channel.h
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#pragma once
#include "Macros.h"

#include <functional>

class Socket;
class EventLoop;
class Channel {
 public:
  Channel(EventLoop *loop, int fd);
  ~Channel();

  DISALLOW_COPY_AND_MOVE(Channel);

  void HandleEvent();
  void EnableRead();

  int GetFd();
  int GetListenEvents();
  int GetReadyEvents();
  bool GetExist();
  void SetExist(bool in = true);
  void UseET();

  void SetReadyEvents(int ev);
  void SetReadCallback(std::function<void()> const &callback);

  static const int kReadEvent;
  static const int kWriteEvent;
  static const int kET;

 private:
  EventLoop *loop_;
  int fd_;
  int listen_events_{0};
  int ready_events_{0};
  bool exist_{false};
  std::function<void()> read_callback_;
  std::function<void()> write_callback_;
};
