#include "binary_context.h"
#include "utils.h"

#include <sstream>


void binary_context::load(elf_reader* elf) {
    section* sec_text = elf->get_text_section();
    Elf64_Addr text_addr = sec_text->get_addr();
    Elf64_Addr last_addr = text_addr;
    symbols* symtab = elf->get_symbols();
    auto func_symbols = symtab->get_func_symbols();

    std::istringstream stream(to_cpp_string(sec_text->get_data(), sec_text->get_size()));

    for(auto& [addr, name] : *func_symbols) {
        std::cout << "ADDR: " << addr << ' ' << "NAME: " << name << std::endl;
        if (addr == last_addr) continue;
        stream.seekg(last_addr);
        
        last_addr = addr;
    }
}