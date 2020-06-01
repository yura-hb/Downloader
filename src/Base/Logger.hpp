#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <iostream>
#include <string>

#include "../Networking/Request.hpp"
#include "../Networking/Response.hpp"
#include "Exception.hpp"

class Logger {
  public:
    /**
     *  @brief
     *    Logs the request sent to the server
     *
     *  Input:
     *    - @param[in] request - request  to sent
     */
    static void logRequest(const Request& request);
    /**
     *  @brief
     *    Logs the parsed headers from the server
     *
     *  Input:
     *    - @param[in] response - response got from the server
     */
    static void logResponse(const Response& response);
    /**
     *  @brief
     *    Logs different exceptions
     *
     *  Input:
     *    - @param[in] exception - exception to log
     */
    static void logError(const Exception& response);
};

#endif
