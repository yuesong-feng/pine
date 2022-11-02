#include "TcpServer.h"
#include "Connection.h"
#include "Socket.h"
#include <cassert>
#include <memory>
#include <iostream>

int main(){
    std::unique_ptr<TcpServer> server = std::make_unique<TcpServer>();
    server->onConnect([](Connection *conn){
        Socket *sock = conn->socket().get();
        std::cout << "New connection. fd: " << sock->fd() << " ip: " << sock->get_ip() << " port: " << sock->get_port() << std::endl;
    });
    server->onRecv([](Connection *conn){
        Socket *sock = conn->socket().get();
        std::cout << "Recv message from fd " << sock->fd() << ": "  << conn->recv_buf() << std::endl;
        conn->set_send_buf(conn->recv_buf());
        conn->Send();
    });
    server->Start();
    return 0;
}
