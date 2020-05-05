#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <iostream>
#include <string>
#include <exception>

class Exception: public std::exception {
  public:
    Exception(const std::string& object): object(object) {}

    const char * what() const noexcept;
  private:
    const std::string object;
};

#endif
