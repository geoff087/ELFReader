/*


*/

#pragma once

#include "elf_reader.h"
#include "binary_context.h"

class rewrite_instace {
public:
    rewrite_instace(const std::string& path)
        : _file_path(path) 
    {
        _elf = std::make_unique<elf_reader>();
    }

    void run();
private:
    std::string _file_path;
    std::unique_ptr<elf_reader> _elf;
    std::unique_ptr<binary_context> _bctx;
};