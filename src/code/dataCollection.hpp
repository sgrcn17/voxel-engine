#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "nlohmann/json.hpp"
#include "dataCollectionType.hpp"

using json = nlohmann::json;

template <typename T>
class DataCollection {
    static_assert(std::is_base_of<DataCollectionType, T>::value, "T must inherit from DataCollectionType");

public:
    DataCollection() = delete;
    DataCollection(const std::string& _path) : path(_path) {}

    void LoadData() {
        std::ifstream file(path);
        json j;
        try {
            file >> j;
        } catch(const json::parse_error& e) {
            std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
            return;
        }
        for(auto& item : j) {
            T obj;
            obj.LoadData(item);
            data.push_back(obj);
        }
    }

    void SaveData() {
        std::ofstream file(path);
        json j;
        for(auto& item : data) {
            json obj;
            item.SaveData(obj);
            j.push_back(obj);
        }

        file << j.dump(4);
    }

    const T& operator[](int idx) const { return data[idx]; }
    T& operator[](int idx) { return data[idx]; }
    size_t size() const { return data.size(); }

private:
    std::string path;
    std::vector<T> data;
};