#include <Connection.h>
#include <Socket.h>
#include <iostream>

int main() {
  Socket *sock = new Socket();
  sock->Connect("127.0.0.1", 1234);

  Connection *conn = new Connection(nullptr, sock);
  if (conn->GetState() == Connection::State::Connected) {
    std::cout << "Connected to server!" << std::endl;
  }

  delete conn;
  return 0;
}
