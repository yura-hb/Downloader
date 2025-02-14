#include "Socket.hpp"

Socket::Socket(const char * hostname, const char *port): hostname(hostname), port(port) {}
Socket::~Socket() {
  if (isConnected())
    disconnect();
  freeAddrInfo();
}

bool Socket::connect() {
  if (!loadAddrInfo())
    return false;

  auto item = info;

  for (; item != nullptr; item = item -> ai_next) {
    if ((socketFileDescriptor = socket(item -> ai_family, item -> ai_socktype, item -> ai_protocol)) == -1) {
      logError(SOCKET_ERROR);
      continue;
    }
    if ((::connect(socketFileDescriptor, item -> ai_addr, item -> ai_addrlen)) == -1) {
      close(socketFileDescriptor);
      logError(CONNECT_ERROR, std::to_string(socketFileDescriptor));
      continue;
    }

    break;
  }

  freeAddrInfo();

  if (item == nullptr) {
    socketFileDescriptor = EMPTY_SOCKET;

    logError(CONNECT_ERROR);
    return false;
  }

  return true;
}

bool Socket::disconnect() {
  if (isConnected())
    return true;

  if (close(socketFileDescriptor) == -1) {
    logError(DISCONNECT_ERROR);
    socketFileDescriptor = EMPTY_SOCKET;
    return false;
  }
  socketFileDescriptor = EMPTY_SOCKET;
  return true;
}

bool Socket::send(const std::string &message, uint32_t &sent) const {
  if (!isConnected())
    return false;

  uint32_t size = message.size();
  int result = 0;
  const char *buf = message.c_str();

  sent = 0;

  while (sent < size) {
    result = ::send(socketFileDescriptor, buf + sent, size, 0);
    if (result == -1) {
     logError(SEND_ERROR, message);
     return false;
    }
    sent += result;
    size -= result;
  }

  return true;
}

bool Socket::read(char * &str, const uint32_t &size, uint32_t &readBytesSize) const {
  if (!isConnected())
    return false;

  readBytesSize = 0;
  int readResult = recv(socketFileDescriptor, str, size, 0);

  if (readResult == -1) {
    logError(DOWNLOAD_ERROR, str);
    return false;
  }

  readBytesSize = readResult;
  str[readBytesSize] = '\0';

  return true;
}

void Socket::setupHints() {
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
}

bool Socket::loadAddrInfo() {
  freeAddrInfo();

  setupHints();

  int status = 0;

  if ((status = getaddrinfo(hostname, port, &hints, &info)) == -1) {
    freeAddrInfo();
    logError(GAI_ERROR, gai_strerror(status));
    return false;
  }

  return true;
}

void Socket::freeAddrInfo() {
  if (info != nullptr)
    freeaddrinfo(info);

  info = nullptr;
}

bool Socket::isConnected() const {
  return socketFileDescriptor != EMPTY_SOCKET;
}

void Socket::logError(Socket::SocketError error, std::string info) const {
  switch (error) {
    case GAI_ERROR:
      Logger::logError(Exception( "Socket: Error during loading addrinfo " + info));
      break;
    case SOCKET_ERROR:
      Logger::logError(Exception("Socket: Error during loading socket" + info));
      break;
    case CONNECT_ERROR:
      Logger::logError(Exception("Socket: Error during connecting to the socket" + info));
      break;
    case DISCONNECT_ERROR:
      Logger::logError(Exception("Socket: Failed to connect" + info));
      break;
    case SEND_ERROR:
      Logger::logError(Exception("Socket: Failed to send  " + info));
      break;
    case DOWNLOAD_ERROR:
      Logger::logError(Exception("Socket: Download failed " + info));
      break;
  }
}
