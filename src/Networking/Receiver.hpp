#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "Socket.hpp"
#include "../Base/Data.hpp"

/**
 * Help class, to manage reading the message from the socket
 */
class Receiver {
  public:
    /**
     * @brief Implements logic for downloading the whole page with the blocks of the bufSize, until CR LF is received.
     *
     * @param[in] - str - output string reference
     * @param[in] - socket - connected socket
     */
    void receivePage(Data<> &str, const Socket &sock);
  private:
    const size_t bufSize = 1024;
};


#endif
