# pine

A high-performance and easy-to-use C++ network library for study.

Now this is just a toy library for education purpose, do not use in production.

## example

An echo server:

```cpp
#include <iostream>
#include "pine.h"

int main() {
  TcpServer *server = new TcpServer();

  Signal::signal(SIGINT, [&] {
    delete server;
    std::cout << "\nServer exit!" << std::endl;
    exit(0);
  });

  server->onConnect([](Connection *conn) { std::cout << "New connection fd: " << conn->socket()->fd() << std::endl; });

  server->onRecv([](Connection *conn) {
    std::cout << "Message from client " << conn->read_buf()->c_str() << std::endl;
    conn->Send(conn->read_buf()->c_str());
  });

  server->Start();

  delete server;
  return 0;
}
```

An echo client:

```cpp
#include "pine.h"
#include <iostream>

int main() {
  Socket *sock = new Socket();
  sock->Create();
  sock->Connect("127.0.0.1", 1234);

  Connection *conn = new Connection(sock->fd(), nullptr);

  while (true) {
    std::string input;
    std::getline(std::cin, input);
    conn->set_send_buf(input.c_str());
    conn->Write();
    if (conn->state() == Connection::State::Closed) {
      conn->Close();
      break;
    }
    conn->Read();
    std::cout << "Message from server: " << conn->read_buf()->c_str() << std::endl;
  }

  delete conn;
  delete sock;
  return 0;
}

```

An HTTP web server:

## build & run
build the pine library
```bash
mkdir build && cd build
cmake .. # for debug, add -DCMAKE_BUILD_TYPE=DEBUG

make format      # optional
make cpplint      # optional
make clang-tidy  # optional
make
```

build tests files, at `pine/build`
```bash
make build-tests
```

Need to run your own tests? Write your program in "test/" directory, eg. server.cpp
```bash
# at pine/build
make server
./bin/server
```

run the echo server
```bash
./bin/echo_server &
./bin/echo_client
```
