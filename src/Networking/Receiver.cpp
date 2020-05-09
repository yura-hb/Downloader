#include "Receiver.hpp"

void Receiver::receivePage(Data<> &str, const Socket &sock) {
  uint32_t receivedSize = 0;

	char *buffer = new char[bufSize + 1];

  memset(buffer, '\0', bufSize + 1);

  while (sock.read(buffer, bufSize, receivedSize) && receivedSize > 0) {
    str.append(buffer, receivedSize);
    memset(buffer, '\0', bufSize + 1);
  }

  delete [] buffer;
}
