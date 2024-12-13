#pragma once

#include <cstdint>

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

// Segment header
struct Elf32_Phdr {
    Elf_Word   p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    Elf_Word   p_filesz;
    Elf_Word   p_memsz;
    Elf_Word   p_flags;
    Elf_Word   p_align;
};

struct Elf64_Phdr {
    Elf_Word   p_type;
    Elf_Word   p_flags;
    Elf64_Off  p_offset;
    Elf64_Addr p_vaddr;
    Elf64_Addr p_paddr;
    Elf_Xword  p_filesz;
    Elf_Xword  p_memsz;
    Elf_Xword  p_align;
};

// Section header
struct Elf32_Shdr {
    Elf_Word   sh_name;
    Elf_Word   sh_type;
    Elf_Word   sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    Elf_Word   sh_size;
    Elf_Word   sh_link;
    Elf_Word   sh_info;
    Elf_Word   sh_addralign;
    Elf_Word   sh_entsize;
};

struct Elf64_Shdr {
    Elf_Word   sh_name;
    Elf_Word   sh_type;
    Elf_Xword  sh_flags;
    Elf64_Addr sh_addr;
    Elf64_Off  sh_offset;
    Elf_Xword  sh_size;
    Elf_Word   sh_link;
    Elf_Word   sh_info;
    Elf_Xword  sh_addralign;
    Elf_Xword  sh_entsize;
};

// Symbol table entry
struct Elf32_Sym {
    Elf_Word      st_name;
    Elf32_Addr    st_value;
    Elf_Word      st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf_Half      st_shndx;
};

struct Elf64_Sym {
    Elf_Word      st_name;
    unsigned char st_info;
    unsigned char st_other;
    Elf_Half      st_shndx;
    Elf64_Addr    st_value;
    Elf_Xword     st_size;
};

#define ELF_ST_BIND( i )    ( ( i ) >> 4 )
#define ELF_ST_TYPE( i )    ( ( i ) & 0xf )
#define ELF_ST_INFO( b, t ) ( ( ( b ) << 4 ) + ( ( t ) & 0xf ) )

#define ELF_ST_VISIBILITY( o ) ( ( o ) & 0x3 )

/////////////////////
// Sections constants

// Section indexes
constexpr Elf_Word SHN_UNDEF     = 0;
constexpr Elf_Word SHN_LORESERVE = 0xFF00;
constexpr Elf_Word SHN_LOPROC    = 0xFF00;
constexpr Elf_Word SHN_HIPROC    = 0xFF1F;
constexpr Elf_Word SHN_LOOS      = 0xFF20;
constexpr Elf_Word SHN_HIOS      = 0xFF3F;
constexpr Elf_Word SHN_ABS       = 0xFFF1;
constexpr Elf_Word SHN_COMMON    = 0xFFF2;
constexpr Elf_Word SHN_XINDEX    = 0xFFFF;
constexpr Elf_Word SHN_HIRESERVE = 0xFFFF;

// Section types
constexpr Elf_Word SHT_NULL               = 0;
constexpr Elf_Word SHT_PROGBITS           = 1;
constexpr Elf_Word SHT_SYMTAB             = 2;
constexpr Elf_Word SHT_STRTAB             = 3;
constexpr Elf_Word SHT_RELA               = 4;
constexpr Elf_Word SHT_HASH               = 5;
constexpr Elf_Word SHT_DYNAMIC            = 6;
constexpr Elf_Word SHT_NOTE               = 7;
constexpr Elf_Word SHT_NOBITS             = 8;
constexpr Elf_Word SHT_REL                = 9;
constexpr Elf_Word SHT_SHLIB              = 10;
constexpr Elf_Word SHT_DYNSYM             = 11;
constexpr Elf_Word SHT_INIT_ARRAY         = 14;
constexpr Elf_Word SHT_FINI_ARRAY         = 15;
constexpr Elf_Word SHT_PREINIT_ARRAY      = 16;
constexpr Elf_Word SHT_GROUP              = 17;
constexpr Elf_Word SHT_SYMTAB_SHNDX       = 18;
constexpr Elf_Word SHT_GNU_ATTRIBUTES     = 0x6ffffff5;
constexpr Elf_Word SHT_GNU_HASH           = 0x6ffffff6;
constexpr Elf_Word SHT_GNU_LIBLIST        = 0x6ffffff7;
constexpr Elf_Word SHT_CHECKSUM           = 0x6ffffff8;
constexpr Elf_Word SHT_LOSUNW             = 0x6ffffffa;
constexpr Elf_Word SHT_SUNW_move          = 0x6ffffffa;
constexpr Elf_Word SHT_SUNW_COMDAT        = 0x6ffffffb;
constexpr Elf_Word SHT_SUNW_syminfo       = 0x6ffffffc;
constexpr Elf_Word SHT_GNU_verdef         = 0x6ffffffd;
constexpr Elf_Word SHT_GNU_verneed        = 0x6ffffffe;
constexpr Elf_Word SHT_GNU_versym         = 0x6fffffff;
constexpr Elf_Word SHT_LOOS               = 0x60000000;
constexpr Elf_Word SHT_HIOS               = 0x6fffffff;
constexpr Elf_Word SHT_LOPROC             = 0x70000000;
constexpr Elf_Word SHT_ARM_EXIDX          = 0x70000001;
constexpr Elf_Word SHT_ARM_PREEMPTMAP     = 0x70000002;
constexpr Elf_Word SHT_ARM_ATTRIBUTES     = 0x70000003;
constexpr Elf_Word SHT_ARM_DEBUGOVERLAY   = 0x70000004;
constexpr Elf_Word SHT_ARM_OVERLAYSECTION = 0x70000005;
constexpr Elf_Word SHT_HIPROC             = 0x7FFFFFFF;
constexpr Elf_Word SHT_LOUSER             = 0x80000000;
// Used by Nintendo Wii U
constexpr Elf_Word SHT_RPL_EXPORTS  = 0x80000001;
constexpr Elf_Word SHT_RPL_IMPORTS  = 0x80000002;
constexpr Elf_Word SHT_RPL_CRCS     = 0x80000003;
constexpr Elf_Word SHT_RPL_FILEINFO = 0x80000004;
constexpr Elf_Word SHT_HIUSER       = 0xFFFFFFFF;

// Symbol types
constexpr Elf_Word STT_NOTYPE            = 0;
constexpr Elf_Word STT_OBJECT            = 1;
constexpr Elf_Word STT_FUNC              = 2;
constexpr Elf_Word STT_SECTION           = 3;
constexpr Elf_Word STT_FILE              = 4;
constexpr Elf_Word STT_COMMON            = 5;
constexpr Elf_Word STT_TLS               = 6;
constexpr Elf_Word STT_LOOS              = 10;
constexpr Elf_Word STT_AMDGPU_HSA_KERNEL = 10;
constexpr Elf_Word STT_HIOS              = 12;
constexpr Elf_Word STT_LOPROC            = 13;
constexpr Elf_Word STT_HIPROC            = 15;