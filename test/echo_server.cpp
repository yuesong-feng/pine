#include <iostream>
#include "pine.h"

int main() {
  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);

  Signal::signal(SIGINT, [&] {
    delete server;
    delete loop;
    std::cout << "\nServer exit!" << std::endl;
    exit(0);
  });
  
  server->NewConnect(
      [](Connection *conn) { std::cout << "New connection fd: " << conn->GetSocket()->GetFd() << std::endl; });

  server->OnConnect([](Connection *conn) {
    conn->Read();
    if (conn->GetState() == Connection::State::Closed) {
      conn->Close();
      return;
    }
    std::cout << "Message from client " << conn->GetSocket()->GetFd() << ": " << conn->ReadBuffer() << std::endl;
    conn->Send(conn->ReadBuffer());
  });

  loop->Loop();
  return 0;
}
