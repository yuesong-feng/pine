# pine

A high-performance and easy-to-use C++ network library for study.

Now this is just a toy library for education purpose, do not use in production.

## example

An echo server:

```cpp
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

  server->OnMessage([](Connection *conn) {
    std::cout << "Message from client " << conn->ReadBuffer() << std::endl;
    if (conn->GetState() == Connection::State::Connected) {
      conn->Send(conn->ReadBuffer());
    }
  });

  loop->Loop();
  return 0;
}

```

An echo client:

```cpp
#include <Connection.h>
#include <Socket.h>
#include <iostream>

int main() {
  Socket *sock = new Socket();
  sock->Connect("127.0.0.1", 1234);

  Connection *conn = new Connection(nullptr, sock);

  while (true) {
    conn->GetlineSendBuffer();
    conn->Write();
    if (conn->GetState() == Connection::State::Closed) {
      conn->Close();
      break;
    }
    conn->Read();
    std::cout << "Message from server: " << conn->ReadBuffer() << std::endl;
  }

  delete conn;
  return 0;
}
```

An HTTP web server:

## build

```bash
mkdir build && cd build
cmake ..
# for debug
cmake -DCMAKE_BUILD_TYPE=DEBUG ..
make format      # optional
make cpplint      # optional
make clang-tidy  # optional
make
# write your program in "test/" directory, eg. server.cpp
make server
./bin/server
```
