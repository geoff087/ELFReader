#pragma once

#include "elf-types.h"
#include "utils.h"

class section {
public:
    virtual ~section() {};
    virtual void load(std::istream& stream, std::streampos offset) = 0;
    virtual void set_index(Elf_Half index) = 0;
    virtual void set_name(const std::string& name) = 0;
    virtual void dump() = 0;
    virtual Elf_Word get_name_idx() = 0;
    virtual std::vector<char> get_data() = 0;
};

template <class T>
class section_impl : public section {
public:
    section_impl(std::shared_ptr<endian_converter> converter)
        : _converter(converter), _name("unknown"), _data()
    {}

    void load(std::istream& stream, std::streampos offset) {
        stream.seekg(offset);
        stream.read(reinterpret_cast<char*>(&_shdr), sizeof _shdr);

        _load_data(stream);
    }

    void dump() {
        std::cout << "============SHDR" << _index << "============" << std::endl;
        std::cout << "sh_name:\t" << _name << '\n';
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

    void set_name(const std::string& name) {
        _name = name;
    }

    std::vector<char> get_data() {
        return _data;
    }

    Elf_Word get_name_idx() {
        return (*_converter)(_shdr.sh_name);
    }

private:
    T _shdr = {};
    std::string _name;
    std::vector<char> _data;
    Elf_Half _index = 0;
    std::shared_ptr<endian_converter> _converter;

    void _load_data(std::istream& stream) {
        if (_shdr.sh_type == SHT_NOBITS) {
            return;
        }
        _data.resize(_shdr.sh_size);
        stream.seekg(_shdr.sh_offset);
        stream.read(reinterpret_cast<char*>(_data.data()), _data.size());
    }
};