#include "Socket.h"
#include "Poller.h"
#include <cassert>
#include <memory>
#include <iostream>

int main()
{
    std::unique_ptr<Socket> serv_sock = std::make_unique<Socket>();
    assert(serv_sock->Create() == RC_SUCCESS);
    assert(serv_sock->Bind() == RC_SUCCESS);
    assert(serv_sock->Listen() == RC_SUCCESS);

    std::unique_ptr<Poller> poller = std::make_unique<PollPoller>();
    poller->Add(serv_sock->fd());

    while (true)
    {
        std::vector<Channel *> active_fds = poller->Poll();
        assert(active_fds.size() == 1);

        std::unique_ptr<Socket> clnt_sock = std::make_unique<Socket>();
        serv_sock->Accept(clnt_sock.get());

        std::cout << "server socket fd: " << serv_sock->fd() << std::endl;
        std::cout << "client socket fd: " << clnt_sock->fd() << std::endl;
    }

    return 0;
}
