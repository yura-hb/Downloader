#ifndef __ABSTRACT_PATTERN__
#define __ABSTRACT_PATTERN__

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "../../Base/Data.hpp"

struct AbstractPattern {
  public:
    using Input = std::pair<std::ifstream&, Data<>&>;
    /**
     * Function, which emits range of the substring values
     */
    using EmitFunction = std::function<void(const std::string& str)>;

    AbstractPattern(const std::string& begin,
                    const std::string& separator,
                    const std::string& end): begin(begin), separator(separator), end(end) {}
    virtual ~AbstractPattern() = default;
    /**
     *  Discussion:
     *    Consumes the bytes from the input stream, and in case, if the pattern matches fill calls emit function.
     *    Otherwise caches the bytes, in buffer.
     *
     *  Input:
     *    - @param[in] input - A pair of input stream and buffer object
     *    - @param[in] func
     *
     *  Output:
     *    - @param[out] - true, in case, if some object matches the pattern.
     */
    virtual bool consume(const Input& input, const EmitFunction& func) const = 0;
  protected:
    const std::string begin;
    const std::string separator;
    const std::string end;
};

#endif
