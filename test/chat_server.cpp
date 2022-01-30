#include <iostream>
#include <map>
#include "Connection.h"
#include "EventLoop.h"
#include "Server.h"
#include "Socket.h"

void Boardcast(std::map<int, Connection*> &clients);
int main() {
  std::map<int, Connection *> clients;

  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);

  server->NewConnect(
      [&](Connection *conn) {
      int clnt_fd = conn->GetSocket()->GetFd();
      std::cout << "New connection fd: " << clnt_fd << std::endl;
      clients[clnt_fd] = conn;
        Boardcast(clients);
  });

  server->OnConnect([&](Connection *conn) {
    conn->Read();
    std::cout << "msg from client: " << conn->ReadBuffer() << std::endl;
    if (conn->GetState() == Connection::State::Closed) {
      conn->Close();
    }
  });

    
  loop->Loop();
  return 0;
}


void Boardcast(std::map<int, Connection*> &clients){
    for(auto &each : clients){
        Connection* conn = each.second;
        conn->Send("Hi everyone, a new client arrived!");
    }
}

