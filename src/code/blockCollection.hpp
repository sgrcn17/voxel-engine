#pragma once

#include "block.hpp"
#include <string>   
#include <vector>

class BlockCollection {
    public:
    static BlockCollection operator[](int index);

    static void LoadData(std::string path);

    private:
    static std::vector<Block> blocks;
};
