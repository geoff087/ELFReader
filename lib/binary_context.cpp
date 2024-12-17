#include "binary_context.h"

void binary_context::load(elf_reader* elf) {
    section* sec_text = elf->get_text_section();
    Elf64_Addr text_addr = sec_text->get_addr();
    symbols* symtab = elf->get_symbols();
    auto func_symbols = symtab->get_func_symbols();

    for(auto& [addr, name] : *func_symbols) {
        std::cout << "ADDR: " << addr << ' ' << "NAME: " << name << std::endl;
    }
}