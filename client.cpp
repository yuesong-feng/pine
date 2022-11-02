#include "Socket.h"
#include <unistd.h>
#include <iostream>

int main() {
    Socket *sock = new Socket();

    sock->Create();
    sock->Connect("127.0.0.1", 8888);
    std::cout << "Connected to server" << std::endl;
    char buf[11];
    memcpy(buf, "1234567890", 11);
    ::write(sock->fd(), buf, 10);
    ::read(sock->fd(), buf, 11);    
    std::cout << "Recv from server: " << buf << std::endl;
    delete sock;
    std::cout << "Disconnected" << std::endl;
    return 0;
}