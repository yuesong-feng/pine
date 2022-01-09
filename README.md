# pine
A high-performance and easy-to-use C++ network library. 

## example
An echo server:
```cpp
int main() {
  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);
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



## build
```bash
mkdir build && cd build
cmake ..
make format      # optional
make cpplin      # optional
make clang-tidy  # optional
make
# write your program in "test/" directory, eg. server.cpp
make server
./bin/server
```
