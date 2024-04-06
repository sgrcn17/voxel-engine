#include "dataLoader.hpp"

DataLoader* DataLoader::instance = nullptr;

DataLoader* DataLoader::GetInstance() {
    if(instance == nullptr) {
        instance = new DataLoader();
        instance->LoadBlockData();
    }
    return instance;
}

BlockData* DataLoader::GetBlockData(int block_id) {
        return (blocksData.count(block_id)) ? blocksData[block_id] : blocksData[0];
}

void DataLoader::LoadBlockData() {
    std::ifstream file("../resources/data/blocks.json");
    json block_data = json::parse(file);

    for (auto& block : block_data) {
        float x = (float)block["x"] / 32.0f;
        float y = (float)block["y"] / 32.0f;
        
        blocksData[block["id"]] = new BlockData(x, y);
    }
}