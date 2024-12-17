#pragma once

#include "binary_function.h"
#include "elf_reader.h"
#include <vector>

class binary_context {
public:
    binary_context() {}
    ~binary_context() {}

    void load(elf_reader* elf);

private:
    std::vector<binary_function> _funcs;
};