#include "Socket.h"

int main() {
    Socket *sock = new Socket();

    sock->Create();
    sock->Connect("127.0.0.1", 8888);

    delete sock;
    return 0;
}