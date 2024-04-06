#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../utils/DataLoader.hpp"

class Block {
public:
    Block() : x(0), y(0), z(0), id(0) {}
    Block(int x, int y, int z, int8_t id) : x(x), y(y), z(z), id(id) {}

    void addVerticesAndIndices(std::vector<float>& vertices, std::vector<unsigned int>& indices);

private:
    int8_t id;
    int x, y, z;
};

#endif