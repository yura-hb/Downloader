#include "Header.hpp"

const std::vector<std::string> Header::store = {
  "Accept",
  "Accept-Charset",
  "Accept-Encoding",
  "Accept-Language",
  "Accept-Ranges",
  "Age",
  "Allow",
  "Authorization",
  "Cache-Control",
  "Connection",
  "Content-Encoding",
  "Content-Language",
  "Content-Length",
  "Content-Location",
  "Content-Type",
  "Date",
  "Except",
  "Host",
  "Location",
  "Pragma"
};

Header::Header(const std::string& header) {
  // All of the types consists of the `Header: Params` format
  auto iter = std::find(header.begin(), header.end(), ':');

  if (iter == header.end())
    throw "Incorrect format of the string";

  auto headerString = std::string(header.begin(), iter - 1);
  auto headerTypeIndex = std::find(store.begin(), store.end(), headerString);

  if (headerTypeIndex == store.end())
    throw "Header is not found";

  this -> header = (_Header)(headerTypeIndex - store.begin());
  parameters = std::string(iter + 1, header.end());
};

std::string Header::convert() const {
  return store[static_cast<int>(header)] + ": " + parameters;
}

std::ostream& operator<< (std::ostream& output, const Header& header) {
  output << header.convert();
  return output;
}

