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

Header::Header(const Data<>& header) {
  auto separator = header.find(":", header.begin());

  if (separator == header.end())
    throw Exception("Incorrect format of the string");

  auto headerName = header.subsequence(header.begin(), separator).stringRepresentation();
  auto headerParams = header.subsequence(separator++, header.end());

  auto headerTypeIndex = std::find_if(store.begin(), store.end(), [headerName](const std::string& str) {
    if (headerName.size() != str.size())
      return false;

    for (auto i = str.begin(), j = headerName.begin(); i != str.end() && j != headerName.end(); i++, j++)
      if (tolower(*i) != tolower(*j))
        return false;

    return true;
  });

  if (headerTypeIndex == store.end())
    throw Exception("Header is not found");

  this -> header = (_Header)(headerTypeIndex - store.begin());
  parameters = headerParams;
}

std::string Header::description() const {
  return store[static_cast<int>(header)] + ": " + parameters.stringRepresentation();
}

std::ostream& operator<< (std::ostream& output, const Header& header) {
  output << header.description();
  return output;
}

