#pragma once

#include "includes.h"

#include "PrefixTree.h"
#include "types.h"

class MemoryManager {
public:
    PrefixTree<Value, string, char> program_data;
    PrefixTree<Type, string, char> names_information;
};

extern unique_ptr<MemoryManager> global_memory;