#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include"ServerConnector.h"

using namespace std;

int main(int argc, char *argv[]) {
  struct addrinfo hints, *res, *p;
  int status;
  char ipstr[INET6_ADDRSTRLEN];

  if (argc != 2) {
    cerr << "Usage showip hostname" << endl;
    return 1;
  }

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(argv[1], nullptr, &hints, &res)) != 0) {
    cerr << "getaddrinfo: " << gai_strerror(status) << endl;
    return 2;
  }

  cout << "IP addresses for: " << argv[1] << endl;

  for (p = res; p != nullptr; p = p -> ai_next) {
    void *addr;
    string ipver;

    // get the pointer to the address itself,
    // different fields in IPv4 and IPv6

    if (p -> ai_family == AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p -> ai_addr;
      addr = &(ipv4 -> sin_addr);
      ipver = "IPv4";
    } else {
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p -> ai_addr;
      addr = &(ipv6 -> sin6_addr);
      ipver = "IPv6";
    }

    inet_ntop(p -> ai_family, addr, ipstr, sizeof(ipstr));

    cout << ipver << ": " << ipstr << endl;
  }

  freeaddrinfo(res);

  return 0;
}
