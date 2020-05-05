#ifndef __INDEXED_REFERENCE__
#define __INDEXED_REFERENCE__

#include "Reference.hpp"

/**
 * Wrapper around the Reference, which defines index in the some string
 */
struct IndexedReference: public Reference {
  public:
    IndexedReference(const std::string& path, const std::pair<int, int>& range): Reference(path), range(range) {}
  protected:
    std::pair<int, int> range;
};

#endif
