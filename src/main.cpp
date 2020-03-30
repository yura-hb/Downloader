#include <iostream>
#include "HTTPClient.hpp"

int main() {

  HTTPClient client;

  std::string buf = "";
  std::string url = "google.com";

  client.loadPage(url, url, buf);

  std::cout << buf << std::endl;

  return 0;
}
