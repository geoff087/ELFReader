#include "rewrite_instance.h"

void rewrite_instance::run() {
    // load elf file.
    _elf->load(_file_path);

    // load bindary context.
    _bctx->load(_elf.get());
}