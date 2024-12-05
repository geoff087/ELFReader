#include <iostream>
#include <fstream>
#include <iomanip>

#include "elf-reader.h"

void read_ehdr() {
  elf_reader reader;
  reader.load("test");
}

int main() {
  read_ehdr();
  return 0;
}