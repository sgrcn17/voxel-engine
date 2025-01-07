#pragma once

#include <string>
#include "dataCollectionType.hpp"

class Texture : DataCollectionType {
    public:
    int xPos, yPos;
    std::string name;

    int GetID() const override {
        return DataCollectionType::id;
    }

    void LoadData(const json& data) override {
        DataCollectionType::id = data["id"];
        xPos = data["position"]["x"];
        yPos = data["position"]["y"];
        name = data["name"];
    }

    void SaveData(json& data) const override {
        data["id"] = DataCollectionType::id;
        data["position"]["x"] = xPos;
        data["position"]["y"] = yPos;
        data["name"] = name;
    }
};