#ifndef __SOCKET_H__
#define __SOCKET_H__

// C++ Core
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
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
    ~Socket();

    /**
     * Discussion:
     *   Connects to the socket at the specific port and hostname.
     *   The connection logic is the next:
     *     1. Load address info. It is the linked list of the struct addrinfo
     *     2. Try to get socket and connect to it.
     *     3. If no socket is found return false
     *
     *   After connections frees info linked list
     */
    bool connect();
    /**
     * Discussion:
     *   Disconnects from the server
     */
    bool disconnect();
    /**
     *  Discussion:
     *    Sends message to the server.
     *
     *    This method consists of the 3 steps:
     *
     *     1. Validate, if we are connected to the socket.
     *     2. Send message to the server using send().
     *        The process of sending can fail or write only part of the string, so tries to send all content until the end of the message.
     *        In case of error logs SEND_ERROR.
     *     3. Returns true in case of the success and sets the number of sent bits.
     *
     *  Input:
     *    @param[in] message - message to send
     *    @param[in] sent - reference to the number of sent bytes
     *
     *  Output:
     *    @param[out] sent - number of sent bytes
     */
    bool send(const std::string &message, uint32_t &sent) const;
    /**
     *  Discussion:
     *    Reads a buffer size from the socket.
     *
     *    This method consists of the 3 steps:
     *     1. Validate, if we are connected to the server
     *     2. Read until to the buffer at min of size (size + 1), in case of the error logs it to the console.
     *     3. Returns true, in case of success and sets reference and size of the read bytes (readSize)
     *
     *  Input:
     *    @param[in] str - reference of the pointer to the buffer
     *    @param[in] size - size of the buffer to read
     *    @param[in] readBytesSize - reference to the number of read bytes
     *
     *  Output:
     *    @param[out] str - filled buffer
     *    @param[out] readBytesSize - count of the read bytes
     *
     */
    bool read(char * &str, const uint32_t &size, uint32_t &readBytesSize) const;
  private:
    const char *hostname, *port;
    struct addrinfo hints, *info = nullptr;
    int socketFileDescriptor;
    static const int EMPTY_SOCKET = -1;
    //  - Helpers
    /**
     *  Discussion:
     *    Logs the socket error to the error channel
     *
     *  Input:
     *    @param[in] - Socket error
     *    @param[in] - info additional info to log
     */
    void logError(SocketError error, std::string info = "") const;
    /**
     *  Discussion:
     *    Configure socket loader hints
     */
    void setupHints();
    /**
     *  Discussion:
     *    Frees the old address and setups the new one
     *
     *  Output:
     *    @param[out] - true, in case if no errors during the add info occured
     */
    bool loadAddrInfo();
    /**
     *  Discussion:
     *    Frees address info
     */
    void freeAddrInfo();
    /**
     *  Discussion:
     *    Returns true, while connected to some socket
     *
     *  Output:
     *    @param[out] - true, in case if connected
     */
    bool isConnected() const;
};

#endif
