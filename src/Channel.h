#pragma once

class Channel {
public:
    Channel();
    ~Channel();
    int fd();
    short events();
    void handleEvent();
private:
    int fd_;
    short events_;
};