# pine
A high-performance and easy-to-use C++ network library. 

Now this is just a toy library for education purpose, do not use in production.

## example
An echo server:
```cpp
int main() {
  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);
  server->NewConnect([](Connection *conn) { 
    std::cout << "New connection fd: " << conn->GetSocket()->GetFd() << std::endl;
  });
  server->OnConnect([](Connection *conn) {
    conn->Read();
    if (conn->GetState() == Connection::State::Closed) {
      conn->Close();
      return;
    }
    conn->SetSendBuffer(conn->ReadBuffer());
    conn->Write();
  });

  loop->Loop();
  delete server;
  delete loop;
  return 0;
}
```
An echo client:
```cpp
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
An muti-user chat room server:

An muti-user chat room client:

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
