#ifndef __STRING_CONVERTIBLE_H__
#define __STRING_CONVERTIBLE_H__

#include "iostream"

struct StringConvertible {
  public:
    virtual std::string description() const;

    virtual ~StringConvertible() = default;
};


#endif
