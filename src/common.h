#pragma once

class TcpServer;
class EventLoop;
class Poller;
class PollPoller;
class Acceptor;
class Connection;
class Channel;
class Socket;

#define DISALLOW_COPY(cname)       \
    cname(const cname &) = delete; \
    cname &operator=(const cname &) = delete;

#define DISALLOW_MOVE(cname)  \
    cname(cname &&) = delete; \
    cname &operator=(cname &&) = delete;

#define DISALLOW_COPY_AND_MOVE(cname) \
    DISALLOW_COPY(cname);             \
    DISALLOW_MOVE(cname);

enum RC {
    RC_UNDEFINED,
    RC_SUCCESS,
    RC_SOCKET_ERROR,
    RC_POLLER_ERROR,
    RC_CONNECTION_ERROR,
    RC_UNIMPLEMENTED
};
