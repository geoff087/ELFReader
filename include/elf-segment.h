#pragma once

#include "elf-types.h"
#include "utils.h"

class segment {
public:
    virtual ~segment() {};
    virtual void load(std::istream& stream, std::streampos offset) = 0;
    virtual void set_index(Elf_Half index) = 0;
};

template <class T>
class segment_impl : public segment {
public:
    segment_impl(std::shared_ptr<endian_converter> converter)
        : _converter(converter)
        {}

    ~segment_impl() = default;

    void load(std::istream& stream, std::streampos offset) {
        std::cout << "============PHDR" << _index << "============\n";
        stream.seekg(offset);
        stream.read(reinterpret_cast<char*>(&_phdr), sizeof _phdr);
        std::cout << "e_type:\t" << (*_converter)(_phdr.p_type) << '\n';
        std::cout << "p_offset:\t" << (*_converter)(_phdr.p_offset) << '\n';
        std::cout << "p_vaddr:\t" << (*_converter)(_phdr.p_vaddr) << '\n';
        std::cout << "p_paddr:\t" << (*_converter)(_phdr.p_paddr) << '\n';
        std::cout << "p_filesz:\t" << (*_converter)(_phdr.p_filesz) << '\n';
        std::cout << "p_memsz:\t" << (*_converter)(_phdr.p_memsz) << '\n';
        std::cout << "p_flags:\t" << (*_converter)(_phdr.p_flags) << '\n';
        std::cout << "p_align:\t" << (*_converter)(_phdr.p_align) << '\n';
    }

    void set_index(Elf32_Half index) {
        _index = index;
    }
private:
    T _phdr = {};
    Elf_Half _index = 0;
    std::shared_ptr<endian_converter> _converter;
};