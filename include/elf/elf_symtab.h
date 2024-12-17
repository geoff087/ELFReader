#pragma once

#include "elf_section.h"
#include <sstream>
#include <map>

class symbols {
public:
    using funcsym_map = std::map<Elf64_Off, std::string>;
    virtual ~symbols() = default;
    virtual void load() = 0; 
    virtual void set_symtab(section* symtab) = 0;
    virtual void set_strtab(section* strtab) = 0;

    virtual std::shared_ptr<funcsym_map> get_func_symbols() = 0;
};

template <class T>
class symbols_impl : public symbols {
public:
    using sym_type = std::pair<std::string, T>;

    symbols_impl(std::shared_ptr<endian_converter> converter) 
        :_converter(converter)
    {}

    void load() {
        char* data = _symtab->get_data();
        std::cout << "NAME: " << _symtab->get_name() << '\n';
        for(int i = 0; i < _symtab->get_size(); i++) {
            std::cout << (int) data[i] << ' ';
        }
        Elf_Xword sym_section_size = _symtab->get_size();
        Elf_Xword str_section_size = _strtab->get_size();
        std::cout << "SIZE: " << to_cpp_string(_symtab->get_data(), sym_section_size).size() << '\n';
        std::istringstream stream(std::move(to_cpp_string(_symtab->get_data(), sym_section_size)));
        std::istringstream stream_str(std::move(to_cpp_string(_strtab->get_data(), str_section_size)));
        _load_symbol(stream);
        _load_func_symbols(stream_str);
    }

    void set_symtab(section* symtab) {
        _symtab = symtab;
    }

    void set_strtab(section* strtab) {
        _strtab = strtab;
    }

    std::shared_ptr<funcsym_map> get_func_symbols() {
        return _func_symbols;
    }
   
private:
    section* _symtab = nullptr;
    section* _strtab = nullptr;
    std::shared_ptr<endian_converter> _converter;
    std::vector<sym_type> _symbols;
    std::shared_ptr<funcsym_map> _func_symbols = nullptr;

    void _load_symbol(std::istream& stream) {
        Elf_Xword section_size = _symtab->get_size();
        Elf_Xword entry_size = _symtab->get_entsize();
        Elf_Xword entry_num = section_size / entry_size;
        _symbols.resize(entry_num);
        stream.seekg(0);

        for(int i = 0; i < entry_num; i++) {
            stream.read(reinterpret_cast<char*>(&_symbols[i].second), sizeof(T));
            std::cout << "============SYMBOL" << i << "============" << std::endl;
            std::cout << "st_name:\t" << (*_converter)(_symbols[i].second.st_name) << '\n';
            std::cout << "st_value:\t" << (*_converter)(_symbols[i].second.st_value) << '\n';
            std::cout << "st_size:\t" << (*_converter)(_symbols[i].second.st_size) << '\n';
            std::cout << "st_info:\t" << (int)(*_converter)(_symbols[i].second.st_info) << '\n';
            std::cout << "st_other:\t" << (int)(*_converter)(_symbols[i].second.st_other) << '\n';
            std::cout << "st_shndx:\t" << (*_converter)(_symbols[i].second.st_shndx) << '\n';
        }
    }

    // this stream reads the data of section '.strtab'
    void _load_func_symbols(std::istringstream& stream) {
        _func_symbols = std::make_shared<funcsym_map>();
        for(sym_type& sym : _symbols) {
            if (ELF_ST_TYPE(sym.second.st_info) == STT_FUNC) {
                stream.seekg((*_converter)(sym.second.st_name));
                // >> read the string including '\0', use c_str() to cut. 
                stream >> sym.first;
                sym.first = std::string(sym.first.c_str());
                (*_func_symbols)[(*_converter)(sym.second.st_value)] = sym.first;
                std::cout << "SYMBOL-FUNC: " << sym.first.c_str() << ' ' << (*_converter)(sym.second.st_size) << std::endl;
            }
        }
    }
};