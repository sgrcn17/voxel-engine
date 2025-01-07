#pragma once

#include <string>
#include <vector>
#include "settings.hpp"
#include "dataCollectionType.hpp"

class Model : DataCollectionType {
public:
    std::string name;
    int textureId[6];

    int GetID() const override {
        return DataCollectionType::id;
    }

    void LoadData(const json& data) override {
        DataCollectionType::id = data["id"];
        name = data["name"];
        textureId[SETTINGS::BLOCK_SIDE::NORTH] = data["textures"]["north"];
        textureId[SETTINGS::BLOCK_SIDE::EAST] = data["textures"]["east"];
        textureId[SETTINGS::BLOCK_SIDE::SOUTH] = data["textures"]["south"];
        textureId[SETTINGS::BLOCK_SIDE::WEST] = data["textures"]["west"];
        textureId[SETTINGS::BLOCK_SIDE::TOP] = data["textures"]["top"];
        textureId[SETTINGS::BLOCK_SIDE::BOTTOM] = data["textures"]["bottom"];
    }

    void SaveData(json& data) const override {
        data["id"] = DataCollectionType::id;
        data["name"] = name;
        data["textures"]["north"] = textureId[SETTINGS::BLOCK_SIDE::NORTH];
        data["textures"]["east"] = textureId[SETTINGS::BLOCK_SIDE::EAST];
        data["textures"]["south"] = textureId[SETTINGS::BLOCK_SIDE::SOUTH];
        data["textures"]["west"] = textureId[SETTINGS::BLOCK_SIDE::WEST];
        data["textures"]["top"] = textureId[SETTINGS::BLOCK_SIDE::TOP];
        data["textures"]["bottom"] = textureId[SETTINGS::BLOCK_SIDE::BOTTOM];
    }
};