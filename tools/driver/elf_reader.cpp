#include <iostream>
#include <fstream>
#include <iomanip>

#include "elf_reader.h"

void read_ehdr(const char* path) {
  elf_reader reader;
  reader.load(path);
}

int main(int argc, char** argv) {
  read_ehdr(argv[1]);
  return 0;
}