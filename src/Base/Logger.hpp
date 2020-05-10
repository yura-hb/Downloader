#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <iostream>
#include <string>

#include "../Networking/Request.hpp"
#include "../Networking/Response.hpp"
#include "Exception.hpp"

static Logger::Level logLevel = Logger::Level::DEBUG;

class Logger {
  public:
    enum class Level {
      INFO, WARNING, DEBUG
    };

    /**
     *  Discussion:
     *    Logs the request sent to the server
     *
     *  Input:
     *    - @param[in] request - request  to sent
     *    - @param[in] level - level to log message. Log in case if level is less than or equal globalLevel level variable.
     */
    static void logRequest(const Request& request, Level level);
    /**
     *  Discussion:
     *    Logs the parsed headers from the server
     *
     *  Input:
     *    - @param[in] response - response got from the server
     *    - @param[in] level - level to log message. Log in case if level is less than or equal globalLevel level variable.
     */
    static void logResponse(const Response& response, Level level);
    /**
     *  Discussion:
     *    Logs different exceptions
     *
     *  Input:
     *    - @param[in] exception - exception to log
     *    - @param[in] level - level to log message. Log in case if level is less than or equal globalLevel level variable.
     */
    static void logError(const Exception& response, Level level);
};

#endif
