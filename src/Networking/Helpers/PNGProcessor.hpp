#ifndef __PNG_PROCESSOR__
#define __PNG_PROCESSOR__

#include <iostream>
#include "../../Templates/Data.hpp"
#include "png.h"

class PNGProcessor {
  public:
    static void processPNGRawData(Data<>& data);
  private:
    /**
     * Size of the PNG header is 8 bytes.
     */
    static size_t pngHeaderLength;

    static bool isPNG(const Data<>& data);
};

#endif
