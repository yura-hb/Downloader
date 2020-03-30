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

  std::cout << std::hex << buffer << std::endl;

  socket.disconnect();

  return 0;
}
