#ifndef __VERSION_H__
#define __VERSION_H__

#include <iostream>
#include <string>
#include <vector>
/**
 * Wrapper around HTTP protocol version
 */
struct Version {
  public:
    enum class _Version {
      v1_1 = 0, v2_0
    };

    Version(const _Version version): version(version) {}

    std::string description() const ;
  private:
    static const std::vector<std::string> store;

    const _Version version;
};

#endif
