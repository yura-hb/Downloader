/**
 * Server implementation
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

#define PORT "3490"
#define MAX_DATA_SIZE 100

void *get_in_addr(struct sockaddr *sa) {
  if (sa -> sa_family == AF_INET)
    return &(((struct sockaddr_in *)sa) -> sin_addr);
  return &(((struct sockaddr_in6 *)sa) -> sin6_addr);
}


int main(int argc, char *argv[]) {
  int sockfd, numbytes; // listen on sock_fd, new connection of new_fd
  char buf[MAX_DATA_SIZE];
  struct addrinfo hints, *servinfo, *p;
  char s[INET6_ADDRSTRLEN];
  int rv;

  char str[100];

  gethostname(str, sizeof(str));
  str[99] = '\0';

  cout << "Hostname" << str << endl;

  if (argc != 2) {
    cerr << "Set hostname only";
    exit(1);
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
    cerr << "Error:" << gai_strerror(rv) << endl;
    return 1;
  }

  for (p = servinfo; p != nullptr; p = p -> ai_next) {
    if ((sockfd = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol)) == -1) {
      perror("server: socket");
      continue;
    }

    if (connect(sockfd, p -> ai_addr, p -> ai_addrlen) == -1) {
      close(sockfd);
      perror("client connect");
      continue;
    }

    break;
  }

  if (p == nullptr) {
    cerr << "Failed to connect";
    return 2;
  }

  inet_ntop(p -> ai_family, get_in_addr((struct sockaddr *) p -> ai_addr), s, sizeof(s));
  cout << "Client connecting" << s << endl;

  freeaddrinfo(servinfo);

  if ((numbytes = recv(sockfd, buf, MAX_DATA_SIZE - 1, 0)) == -1) {
    perror("recv");
    exit(1);
  }

  buf[numbytes] = '\0';

  cout << buf << endl;

  close(sockfd);

  return 0;
}
