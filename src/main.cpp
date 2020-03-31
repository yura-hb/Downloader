#include <iostream>
#include "HTTPClient.hpp"

int main() {

  HTTPClient client;

  std::string buf = "";
  std::string url = "http://en.cppreference.com/w/cpp/string/basic_string/find";

  client.loadPage(url, buf);

  std::cout << buf << std::endl;

  return 0;
}
