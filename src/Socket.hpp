#ifndef __SOCKET_H__
#define __SOCKET_H__

// C++ Core
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <string>
// Socket API
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


class Socket {
  public:
  // - NESTED
    enum SocketError {
      GAI_ERROR,
      SOCKET_ERROR,
      CONNECT_ERROR,
      DISCONNECT_ERROR,
      SEND_ERROR,
      DOWNLOAD_ERROR
    };

    Socket(const char *hostname, const char *port);

    /**
     * Connects to the socket at the specific port and hostname.
     * The connection logic is the next:
     *   1. Load address info. It is the linked list of the struct addrinfo
     *   2. Try to get socket and connect to it.
     *   3. If no socket is found return false
     *
     * After connections frees info linked list
     */
    bool connect();
    /**
     * Disconnects from the server
     */
    bool disconnect();
    /**
     * Sends message to the server.
     *
     * This method consists of the 3 steps:
     *
     *  1. Validate, if we are connected to the socket.
     *  2. Send message to the server using send().
     *     The process of sending can fail or write only part of the string, so tries to send all content until the end of the message.
     *     In case of error logs SEND_ERROR.
     *  3. Returns true in case of the success and sets the number of sent bits.
     *
     * !!! IMPORTANT: Doesn't support delimitering and packaging, so require improvements, but for sending HTTP requests it is enough
     */
    bool send(const std::string &message, uint32_t &sent) const;
    /**
     * Reads a buffer size from the socket.
     *
     * This method consists of the 3 steps:
     *  1. Validate, if we are connected to the server
     *  2. Read until the end of the buffer, in case of the error logs it to the console.
     *  3. Returns true, in case of success and sets reference and size of the read bytes (readSize)
     *
     */
    bool read(std::string &str, const uint32_t &size, uint32_t &readBytesSize) const;

    ~Socket();
  private:
    const char *hostname, *port;
    //  - Server-side logic
    struct addrinfo hints, *info;
    int socketFileDescriptor;
    //  - Constants
    static const int EMPTY_SOCKET = -1;
    //  - Helpers
    void logError(SocketError error, std::string info = "") const;
    void setupHints();
    bool loadAddrInfo();
    bool isConnected() const;
};

#endif
