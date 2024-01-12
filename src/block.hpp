#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Block {
public:
    Block() : x(0), y(0), z(0) {}
    Block(int x, int y, int z);
    void addVerticesAndIndices(std::vector<float>& vertices, std::vector<unsigned int>& indices);

private:
    int x, y, z;
};

#endif