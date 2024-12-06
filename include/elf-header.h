#pragma once

#include "elf-types.h"
#include "utils.h"

class elf_header {
public:
    virtual ~elf_header() {};
    virtual void load(std::istream& file) = 0;
    virtual unsigned char get_class() = 0;
    virtual Elf_Half get_phentsize() = 0;
    virtual Elf_Half get_phnum() = 0;
    virtual Elf64_Off get_phoff() = 0;
    virtual Elf_Half get_shentsize() = 0;
    virtual Elf_Half get_shnum() = 0;
    virtual Elf64_Off get_shoff() = 0;
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
    elf_header_impl(std::shared_ptr<endian_converter> converter) 
        : _converter(converter)
    {}

    void load(std::istream& stream) {
        std::cout << "============ELFHEADER============\n";
        stream.seekg(0);
        stream.read(reinterpret_cast<char *>(&_ehdr), sizeof _ehdr);
        for(int i = 0; i < EI_NIDENT; i++) {
            std::cout << std::setw(2) << std::hex << std::setfill('0') << (int) _ehdr.e_ident[i] << " \n"[i == EI_NIDENT - 1];
        }
        std::cout << "e_type:\t" << (*_converter)(_ehdr.e_type) << '\n';
        std::cout << "e_machine:\t" << (*_converter)(_ehdr.e_machine) << '\n';
        std::cout << "e_version:\t" << (*_converter)(_ehdr.e_version) << '\n';
        std::cout << "e_entry:\t" << (*_converter)(_ehdr.e_entry) << '\n';
        std::cout << "e_phoff:\t" << (*_converter)(_ehdr.e_phoff) << '\n';
        std::cout << "e_shoff:\t" << (*_converter)(_ehdr.e_shoff) << '\n';
        std::cout << "e_flags:\t" << (*_converter)(_ehdr.e_flags) << '\n';
        std::cout << "e_ehsize:\t" << (*_converter)(_ehdr.e_ehsize) << '\n';
        std::cout << "e_phentsize:\t" << (*_converter)(_ehdr.e_phentsize) << '\n';
        std::cout << "e_phnum:\t" << (*_converter)(_ehdr.e_phnum) << '\n';
        std::cout << "e_shentsize:\t" << (*_converter)(_ehdr.e_shentsize) << '\n';
        std::cout << "e_shnum:\t" << (*_converter)(_ehdr.e_shnum) << '\n';
        std::cout << "e_shstrndx:\t" << (*_converter)(_ehdr.e_shstrndx) << '\n';
    }

    unsigned char get_class() {
        return (*_converter)(_ehdr.e_ident[EI_CLASS]);
    }
    Elf_Half get_phentsize() {
        return (*_converter)(_ehdr.e_phentsize);
    }
    Elf_Half get_phnum() {
        return (*_converter)(_ehdr.e_phnum);
    }
    Elf64_Off get_phoff() {
        return (*_converter)(_ehdr.e_phoff);
    }
    Elf_Half get_shentsize() {
        return (*_converter)(_ehdr.e_shentsize);
    }
    Elf_Half get_shnum() {
        return (*_converter)(_ehdr.e_shnum);
    }
    Elf64_Off get_shoff() {
        return (*_converter)(_ehdr.e_shoff);
    }
private:
    T _ehdr = {};
    std::shared_ptr<endian_converter> _converter;
};