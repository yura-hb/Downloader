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
  "Pragma",
  "Transfer-Encoding"
};

Header::Header(const std::string& header) {
  // All of the types consists of the `Header: Params` format
  auto iter = std::find(header.begin(), header.end(), ':');

  if (iter == header.end())
    throw Exception("Incorrect format of the string");

  auto headerString = std::string(header.begin(), iter);

  auto headerTypeIndex = std::find_if(store.begin(), store.end(), [headerString](const std::string& str) {
    if (headerString.size() != str.size())
      return false;

    for (auto i = str.begin(), j = headerString.begin(); i != str.end() && j != headerString.end(); i++, j++)
      if (tolower(*i) != tolower(*j))
        return false;

    return true;
  });

  if (headerTypeIndex == store.end())
    throw Exception("Header is not found");

  this -> header = (_Header)(headerTypeIndex - store.begin());
  // skip : and space
  parameters = std::string(iter + 2, header.end());
}

std::string Header::description() const {
  return store[static_cast<int>(header)] + ": " + parameters;
}

std::ostream& operator<< (std::ostream& output, const Header& header) {
  output << header.description();
  return output;
}

