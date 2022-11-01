#pragma once
#include "common.h"
#include <memory>
class Socket;

class Acceptor {
public:
    DISALLOW_COPY_AND_MOVE(Acceptor);
    Acceptor();
    ~Acceptor();
    RC Accept();
private:
    std::unique_ptr<Socket> socket_;
};
