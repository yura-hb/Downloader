#include <iostream>
#include "Base/ArgumentParser.hpp"

int main(int argc, char *argv[]) {
  return ArgumentParser::handle(argc, argv);;
}
