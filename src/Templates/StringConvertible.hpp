#ifndef __STRING_CONVERTIBLE_H__
#define __STRING_CONVERTIBLE_H__

#include <iostream>

/**
 * Class to provide visual string representation of some model
 */
struct StringConvertible {
  public:
    /**
     * Output:
     *   - @param[out] - description of some model
     */
    virtual std::string description() const;
    virtual ~StringConvertible() = default;
};


#endif
