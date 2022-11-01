#include "Socket.h"
#include "Poller.h"
#include <cassert>
#include <memory>

int main(){
    std::unique_ptr<Socket> serv_sock = std::make_unique<Socket>();
    serv_sock->Create();
    serv_sock->Bind();
    serv_sock->Listen();
    std::unique_ptr<Poller> poller = std::make_unique<PollPoller>();
    poller->Add(serv_sock->fd());
    while(true) {
        
    }
    return 0;
}
