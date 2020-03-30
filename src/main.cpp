#include <iostream>
#include "Socket.hpp"
#include "Receiver.hpp"

int main() {
  Socket socket("google.com", "80");

  socket.connect();

  std::string message = "GET\n";
  uint32_t size = message.size();

  socket.send(message, size);

  std::string buffer = "";

  Receiver rec;

  rec.receivePage(buffer, socket);

  socket.disconnect();

  return 0;
}
