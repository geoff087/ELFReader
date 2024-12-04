#include <iostream>
#include <fstream>
#include <iomanip>

using Elf_Half   = uint16_t;
using Elf_Word   = uint32_t;
using Elf_Sword  = int32_t;
using Elf_Xword  = uint64_t;
using Elf_Sxword = int64_t;

using Elf32_Addr = uint32_t;
using Elf32_Off  = uint32_t;
using Elf64_Addr = uint64_t;
using Elf64_Off  = uint64_t;

using Elf32_Half  = Elf_Half;
using Elf64_Half  = Elf_Half;
using Elf32_Word  = Elf_Word;
using Elf64_Word  = Elf_Word;
using Elf32_Sword = Elf_Sword;
using Elf64_Sword = Elf_Sword;

// Identification index
constexpr unsigned char EI_MAG0       = 0;
constexpr unsigned char EI_MAG1       = 1;
constexpr unsigned char EI_MAG2       = 2;
constexpr unsigned char EI_MAG3       = 3;
constexpr unsigned char EI_CLASS      = 4;
constexpr unsigned char EI_DATA       = 5;
constexpr unsigned char EI_VERSION    = 6;
constexpr unsigned char EI_OSABI      = 7;
constexpr unsigned char EI_ABIVERSION = 8;
constexpr unsigned char EI_PAD        = 9;
constexpr unsigned char EI_NIDENT     = 16;

// Magic number
constexpr unsigned char ELFMAG0 = 0x7F;
constexpr unsigned char ELFMAG1 = 'E';
constexpr unsigned char ELFMAG2 = 'L';
constexpr unsigned char ELFMAG3 = 'F';

// File class
constexpr unsigned char ELFCLASSNONE = 0;
constexpr unsigned char ELFCLASS32   = 1;
constexpr unsigned char ELFCLASS64   = 2;

// Encoding
constexpr unsigned char ELFDATANONE = 0;
constexpr unsigned char ELFDATA2LSB = 1;
constexpr unsigned char ELFDATA2MSB = 2;


struct Elf32_Ehdr {
    unsigned char e_ident[EI_NIDENT];	
    Elf_Half      e_type;
    Elf_Half      e_machine;
    Elf_Word      e_version;
    Elf32_Addr    e_entry;
    Elf32_Off     e_phoff;
    Elf32_Off     e_shoff;
    Elf_Word      e_flags;
    Elf_Half      e_ehsize;
    Elf_Half      e_phentsize;
    Elf_Half      e_phnum;
    Elf_Half      e_shentsize;
    Elf_Half      e_shnum;
    Elf_Half      e_shstrndx;
};

struct Elf64_Ehdr {
    unsigned char e_ident[EI_NIDENT];
    Elf_Half      e_type;
    Elf_Half      e_machine;
    Elf_Word      e_version;
    Elf64_Addr    e_entry;
    Elf64_Off     e_phoff;
    Elf64_Off     e_shoff;
    Elf_Word      e_flags;
    Elf_Half      e_ehsize;
    Elf_Half      e_phentsize;
    Elf_Half      e_phnum;
    Elf_Half      e_shentsize;
    Elf_Half      e_shnum;
    Elf_Half      e_shstrndx;
};

void read_ehdr() {
  std::ifstream elf("test", std::ios::binary);
  if (!elf.is_open()) {
    std::cout << "Can not open elf file\n";
    return;
  } 
  unsigned char e_ident[EI_NIDENT];
  elf.read(reinterpret_cast<char *>(e_ident), sizeof e_ident);
  for(int i = 0; i < EI_NIDENT; i++) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << i << ' ' << (int) e_ident[i] << '\n';
  }

  
}

int main() {
  read_ehdr();
  return 0;
}