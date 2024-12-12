#pragma once

#include "elf-section.h"
#include <sstream>

class symbols {
public:
    virtual ~symbols() = default;
    virtual void load() = 0; 
    virtual void set_symtab(section* symtab) = 0;
};

template <class T>
class symbols_impl : public symbols {
public:
    symbols_impl(std::shared_ptr<endian_converter> converter) 
        :_converter(converter)
    {}

    void load() {
        char* data = _symtab->get_data();
        std::cout << "NAME: " << _symtab->get_name() << '\n';
        for(int i = 0; i < _symtab->get_size(); i++) {
            std::cout << (int) data[i] << ' ';
        }
        Elf_Xword section_size = _symtab->get_size();
        std::cout << "SIZE: " << to_cpp_string(_symtab->get_data(), section_size).size() << '\n';
        std::istringstream stream(std::move(to_cpp_string(_symtab->get_data(), section_size)));
        _load_symbol(stream);
    }

    void set_symtab(section* symtab) {
        _symtab = symtab;
    }
   
private:
    section* _symtab = nullptr;
    std::shared_ptr<endian_converter> _converter;
    std::vector<T> _symbols;

    void _load_symbol(std::istream& stream) {
        Elf_Xword section_size = _symtab->get_size();
        Elf_Xword entry_size = _symtab->get_entsize();
        Elf_Xword entry_num = section_size / entry_size;
        _symbols.resize(entry_num);
        stream.seekg(0);

        for(int i = 0; i < entry_num; i++) {
            stream.read(reinterpret_cast<char*>(&_symbols[i]), sizeof(T));
            std::cout << "============SYMBOL" << i << "============" << std::endl;
            std::cout << "st_name:\t" << (*_converter)(_symbols[i].st_name) << '\n';
            std::cout << "st_value:\t" << (*_converter)(_symbols[i].st_value) << '\n';
            std::cout << "st_size:\t" << (*_converter)(_symbols[i].st_size) << '\n';
            std::cout << "st_info:\t" << (*_converter)(_symbols[i].st_info) << '\n';
            std::cout << "st_other:\t" << (*_converter)(_symbols[i].st_other) << '\n';
            std::cout << "st_shndx:\t" << (*_converter)(_symbols[i].st_shndx) << '\n';
        }
    }
};