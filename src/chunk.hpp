#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Chunk {
public:
    Chunk();

private:
    unsigned int VBO, VAO;
};