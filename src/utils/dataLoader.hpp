#pragma once

#include <map>
#include <utility>
#include <fstream>

#include "../include/nlohmann/json.hpp"
#include "blockData.hpp"

using json = nlohmann::json;

class DataLoader {

public:
    DataLoader(DataLoader &other) = delete;
    void operator=(const DataLoader &) = delete;

    static DataLoader* GetInstance();

    void LoadBlockData();

    BlockData* GetBlockData(int block_id);

protected:
    DataLoader() { }
    static DataLoader* instance;

    std::map<int, BlockData*> blocksData;
};