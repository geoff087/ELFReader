#pragma once

#include "elf-types.h"
#include "utils.h"

class section {
public:
    virtual ~section() {};
    virtual void load(std::istream& stream, std::streampos offset) = 0;
    virtual void set_index(Elf_Half index) = 0;
};

template <class T>
class section_impl : public section {
public:
    section_impl(std::shared_ptr<endian_converter> converter)
        : _converter(converter)
    {}

    void load(std::istream& stream, std::streampos offset) {
        std::cout << "============SHDR" << _index << "============\n";
        stream.seekg(offset);
        stream.read(reinterpret_cast<char*>(&_shdr), sizeof _shdr);
        std::cout << "sh_name:\t" << (*_converter)(_shdr.sh_name) << '\n';
        std::cout << "sh_type:\t" << (*_converter)(_shdr.sh_type) << '\n';
        std::cout << "sh_flags:\t" << (*_converter)(_shdr.sh_flags) << '\n';
        std::cout << "sh_addr:\t" << (*_converter)(_shdr.sh_addr) << '\n';
        std::cout << "sh_offset:\t" << (*_converter)(_shdr.sh_offset) << '\n';
        std::cout << "sh_size:\t" << (*_converter)(_shdr.sh_size) << '\n';
        std::cout << "sh_link:\t" << (*_converter)(_shdr.sh_link) << '\n';
        std::cout << "sh_info:\t" << (*_converter)(_shdr.sh_info) << '\n';
        std::cout << "sh_addralign:\t" << (*_converter)(_shdr.sh_addralign) << '\n';
        std::cout << "sh_entsize:\t" << (*_converter)(_shdr.sh_entsize) << '\n';
    }

    void set_index(Elf_Half index) {
        _index = index;
    }

private:
    T _shdr = {};
    Elf_Half _index = 0;
    std::shared_ptr<endian_converter> _converter;
};