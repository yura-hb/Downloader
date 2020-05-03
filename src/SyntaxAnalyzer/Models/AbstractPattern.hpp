#ifndef __ABSTRACT_PATTERN__
#define __ABSTRACT_PATTERN__

#include <iostream>
#include <vector>
#include <string>
#include <functional>

struct AbstractPattern {
  public:
    /**
     * Active search range
     */
    using Range = std::pair<std::string::iterator&, const std::string::iterator&>;
    /**
     * Pair of indexes
     */
    using IndexRange = std::pair<int, int>;
    /**
     * Function, which emits range of the substring values
     */
    using EmitFunction = std::function<void(IndexRange)>;

    AbstractPattern(const std::string& begin, const std::string& end, const std::string& separator = "=") {}
    /**
     * Consumes string from the current position and validates it with begin
     */
    virtual bool consume(const Range& range, const EmitFunction& func) const = 0;
  protected:
    const::std::string begin;
    const::std::string separator;
    const::std::string end;

    void skipWhitespacesCharacters(const Range& range) const;
    /**
     * Return prefix, if it is the prefix from the iterator
     */
    std::string prefix(const Range& range) const;
  private:
    static std::vector<char> whitespaces;
};

#endif
