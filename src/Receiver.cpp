#include "Receiver.hpp"

void Receiver::receivePage(std::string &str, const Socket &sock) {
  uint32_t receivedSize = 0;

  std:: cout << bufSize << std::endl;
  char *buffer = new char[bufSize + 1];

  memset(buffer, 0, bufSize + 1);

  while (sock.read(buffer, bufSize, receivedSize)) {
    str += buffer;
    memset(buffer, 0, bufSize + 1);
  }

  delete [] buffer;
}
