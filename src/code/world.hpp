#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>
#include <iostream>
#include "chunk.hpp"
#include <glm/gtc/noise.hpp>

class World {
public:
    ~World();

    void Generate();
    void Update();
    void Render();
private:
    void CreateChunk(int x, int z);
    float GenerateHeight(int x, int z);

    //x, z
    std::map<int, std::map<int, Chunk*>> chunks;
};