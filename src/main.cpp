#include <iostream>
#include "Socket.hpp"

int main() {
  Socket socket("google.com", "80");

  socket.connect();

  std::string message = "GET\n";
  uint32_t size = message.size();

  socket.send(message, size);

  std::string buffer = "";

  size = 0;

  socket.read(buffer, 1024, size);

  std::cout << buffer << std::endl;

  socket.disconnect();

  return 0;
}
