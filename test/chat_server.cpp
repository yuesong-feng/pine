#include <iostream>
#include <map>
#include "Connection.h"
#include "EventLoop.h"
#include "Server.h"
#include "Socket.h"

int main() {
  std::map<int, Connection *> clients;

  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);
  server->NewConnect([&](Connection *conn){
          std::cout << "New connection fd: " << conn->GetSocket()->GetFd() << std::endl;
});
  server->OnConnect([&](Connection *conn) {
    conn->Read();
    std::cout << "msg from client: "<<conn->ReadBuffer() <<std::endl;
    if(conn->GetState() == Connection::State::Closed){
        conn->Close();
    }
    
  });

  loop->Loop();
  return 0;
}
