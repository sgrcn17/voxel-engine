#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include <vector>
#include <memory>

#include "config.hpp"

class Chunk {
public:
    Chunk(int chunkX, int chunkZ);
    ~Chunk();

    void Draw();
    void UpdateMesh();

    std::array<unsigned short, CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE> blockID;

    bool updated = false;
private:
    int x, z;   
    unsigned int VBO, VAO, EBO;

    std::vector<> vertices;
    std::vector<unsigned short> indices;
};