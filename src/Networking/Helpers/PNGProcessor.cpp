#include "PNGProcessor.hpp"

size_t PNGProcessor::pngHeaderLength = 8;

bool PNGProcessor::isPNG(const Data<>& data) {
  Data<> header = data.subsequence(data.begin(), data.at(pngHeaderLength - 1));
  std::string headerStr = header.stringRepresentation();

  return !png_sig_cmp((png_const_bytep)headerStr.c_str(), 0, pngHeaderLength - 1);
}
