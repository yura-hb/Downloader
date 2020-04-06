#include <iostream>
#include "HTTPClient.hpp"

int main() {

  HTTPClient client;

  std::string buf = "";
  std::string url = "www.google.com";

  client.loadPage(url, buf);

  return 0;
}
