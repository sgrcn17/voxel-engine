#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include <vector>

#include "config.hpp"

class Chunk {
public:
    Chunk(int chunkX, int chunkZ);
    Chunk() = delete;
    ~Chunk();

    void Draw();
    void UpdateMesh();

private:
    int x, z;
    unsigned int VBO, VAO, EBO;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::array<int, CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE> blockID;
};