#pragma once

#include "elf-header.h"
#include "utils.h"
#include <string>
#include <fstream>
#include <iostream>

class elf_reader {
public:
    elf_reader() :_converter(std::make_shared<endian_converter>()) {}
    elf_reader(const char* path) {

    }
    ~elf_reader() = default;

    void load(const char* path) {
        pstream = std::make_unique<std::ifstream>();
        pstream->open(path, std::ios::in | std::ios::binary);
        if (!pstream->is_open()) {
            std::cout << "Can not open elf file\n";
            return;
        } 
        unsigned char e_ident[EI_NIDENT];
        pstream->read(reinterpret_cast<char *>(e_ident), sizeof e_ident);
        std::cout << "first read :\n";
        for(int i = 0; i < EI_NIDENT; i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << i << ' ' << (int) e_ident[i] << '\n';
        }
        _converter->setup(e_ident[EI_DATA]);
        create_header(e_ident[EI_CLASS], e_ident[EI_DATA]);
        _ehdr->load(*pstream);
    }

    
private:
    std::unique_ptr<std::ifstream> pstream = nullptr;
    std::unique_ptr<elf_header> _ehdr;
    std::shared_ptr<endian_converter> _converter;

    void create_header(unsigned char file_class, unsigned char encoding) {
        if (file_class == ELFCLASS32) {
            _ehdr = std::make_unique<elf_header_impl<Elf32_Ehdr>>(_converter);
        } else if (file_class == ELFCLASS64) {
            _ehdr = std::make_unique<elf_header_impl<Elf64_Ehdr>>(_converter);
        }
    }
};