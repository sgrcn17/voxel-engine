#pragma once

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class DataCollectionType {
 public:
    virtual ~DataCollectionType() = default;

    virtual void LoadData(const json& data) = 0;
    virtual void SaveData(json& data) const = 0;

protected:
    unsigned int id;
};