#include <iostream>
#include <fstream>
#include <iomanip>

#include "rewrite_instance.h"

void read_ehdr(const char* path) {
  rewrite_instance RI(path);
  RI.run();
}

int main(int argc, char** argv) {
  read_ehdr(argv[1]);
  return 0;
}