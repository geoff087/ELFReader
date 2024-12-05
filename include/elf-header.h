#pragma once

#include "elf-types.h"

class elf_header {
public:
    virtual ~elf_header() {};
    virtual void load(std::istream& file) = 0;
};

template <class T> struct elf_header_type;
template <> struct elf_header_type<Elf32_Ehdr> {
    using Phdr_type                       = Elf32_Phdr;
    // using Shdr_type                       = Elf32_Shdr;
    static const unsigned char file_class = ELFCLASS32;
};
template <> struct elf_header_type<Elf64_Ehdr> {
    using Phdr_type                       = Elf64_Phdr;
    // using Shdr_type                       = Elf32_Shdr;
    static const unsigned char file_class = ELFCLASS64;
};

template <class T>
class elf_header_impl : public elf_header {
public:
    void load(std::istream& stream) {
        stream.seekg(0);
        stream.read(reinterpret_cast<char *>(&_ehdr), sizeof _ehdr);
        std::cout << "============ELFHEADER============\n";
        for(int i = 0; i < EI_NIDENT; i++) {
            std::cout << std::setw(2) << std::hex << std::setfill('0') << (int) _ehdr.e_ident[i] << " \n"[i == EI_NIDENT - 1];
        }
        std::cout << "e_type:\t" << _ehdr.e_type << '\n';
        std::cout << "e_machine:\t" << _ehdr.e_machine << '\n';
        std::cout << "e_version:\t" << _ehdr.e_version << '\n';
        std::cout << "e_entry:\t" << _ehdr.e_entry << '\n';
        std::cout << "e_phoff:\t" << _ehdr.e_phoff << '\n';
        std::cout << "e_shoff:\t" << _ehdr.e_shoff << '\n';
        std::cout << "e_flags:\t" << _ehdr.e_flags << '\n';
        std::cout << "e_ehsize:\t" << _ehdr.e_ehsize << '\n';
        std::cout << "e_phentsize:\t" << _ehdr.e_phentsize << '\n';
        std::cout << "e_phnum:\t" << _ehdr.e_phnum << '\n';
        std::cout << "e_shentsize:\t" << _ehdr.e_shentsize << '\n';
        std::cout << "e_shnum:\t" << _ehdr.e_shnum << '\n';
        std::cout << "e_shstrndx:\t" << _ehdr.e_shstrndx << '\n';
    }
private:
    T _ehdr = {};
};