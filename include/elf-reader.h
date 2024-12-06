#pragma once

#include "elf-header.h"
#include "elf-segment.h"
#include "elf-section.h"
#include "utils.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class elf_reader {
public:
    elf_reader() :_converter(std::make_shared<endian_converter>()) {}
    elf_reader(const char* path) {

    }

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
        load_segments(*pstream);
        load_sections(*pstream);
    }

    
private:
    std::unique_ptr<std::ifstream> pstream = nullptr;
    std::unique_ptr<elf_header> _ehdr;
    std::vector<std::unique_ptr<segment>> _segments;
    std::vector<std::unique_ptr<section>> _sections;
    std::shared_ptr<endian_converter> _converter;

    void create_header(unsigned char file_class, unsigned char encoding) {
        if (file_class == ELFCLASS32) {
            _ehdr = std::make_unique<elf_header_impl<Elf32_Ehdr>>(_converter);
        } else if (file_class == ELFCLASS64) {
            _ehdr = std::make_unique<elf_header_impl<Elf64_Ehdr>>(_converter);
        }
    }

    std::unique_ptr<segment> create_segment(unsigned char file_class) {
        std::unique_ptr<segment> seg;
        if (file_class == ELFCLASS32) {
            seg = std::make_unique<segment_impl<Elf32_Phdr>>(_converter);
        } else if (file_class == ELFCLASS64) {
            seg = std::make_unique<segment_impl<Elf64_Phdr>>(_converter);
        }
        return seg;
    }

    std::unique_ptr<section> create_section(unsigned char file_class) {
        std::unique_ptr<section> sec;
        if (file_class == ELFCLASS32) {
            sec = std::make_unique<section_impl<Elf32_Shdr>>(_converter);
        } else if (file_class == ELFCLASS64) {
            sec = std::make_unique<section_impl<Elf64_Shdr>>(_converter);
        }
        return sec;
    }

    void load_segments(std::istream& stream) {
        unsigned char file_class = _ehdr->get_class();
        Elf_Half entry_size = _ehdr->get_phentsize();
        Elf_Half entry_num = _ehdr->get_phnum();
        Elf64_Off offset = _ehdr->get_phoff();

        for (int i = 0; i < entry_num; i++) {
            _segments.emplace_back(create_segment(file_class));
            _segments.back()->set_index(i);
            _segments.back()->load(stream, offset + i * entry_size);
        }
    }

    void load_sections(std::istream& stream) {
        unsigned char file_class = _ehdr->get_class();
        Elf_Half entry_size = _ehdr->get_shentsize();
        Elf_Half entry_num = _ehdr->get_shnum();
        Elf64_Off offset = _ehdr->get_shoff();

        for (int i = 0; i < entry_num; i++) {
            _sections.emplace_back(create_section(file_class));
            _sections.back()->set_index(i);
            _sections.back()->load(stream, offset + i * entry_size);
        }
    }
};