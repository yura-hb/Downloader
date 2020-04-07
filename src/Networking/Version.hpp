#ifndef __VERSION_H__
#define __VERSION_H__

#include "iostream"
#include "string"
#include "vector"
#include "../Templates/StringConvertible.hpp"

struct Version: public StringConvertible {
  public:
    enum class _Version {
      v1_1 = 0, v2_0
    };

    Version(const _Version version): version(version) {}

    std::string convert() const override;
  private:
    static const std::vector<std::string> store;

    const _Version version;
};

#endif
