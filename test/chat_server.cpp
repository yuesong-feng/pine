#include <iostream>
#include <map>
#include "Connection.h"
#include "EventLoop.h"
#include "Server.h"

int main() {
  std::map<int, Connection *> clients;

  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);
  server->OnConnect([&](Connection *conn) {

  });

  loop->Loop();
  return 0;
}
