#include "DataLoader.hpp"

DataLoader* DataLoader::instance = nullptr;

DataLoader* DataLoader::GetInstance() {
    if(instance == nullptr) {
        instance = new DataLoader();
        instance->LoadBlockData();
    }
    return instance;
}

std::pair<float,float> DataLoader::GetBlockData(int block_id) {
        return (blockData.count(block_id)) ? blockData[block_id] : blockData[0];
}

void DataLoader::LoadBlockData() {
    std::ifstream file("../resources/data/blocks.json");
    json block_data = json::parse(file);

    for (auto& block : block_data) {
        float x = (float)block["x"] / 32.0f;
        float y = (float)block["y"] / 32.0f;
        blockData[block["id"]] = std::make_pair(x, y);
    }
}