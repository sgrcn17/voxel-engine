#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "../render/shader.hpp"
#include "../render/vao.hpp"
#include "../render/vbo.hpp"
#include "../render/ebo.hpp"
#include "../core/block.hpp"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Chunk {
public:
    Chunk(int x, int y, int z, const Shader& shaderProgram);

    void RemoveBlock(int x, int y, int z);
    void Draw();

private:

    void UpdateMesh();

    static const int CHUNK_SIZE_X = 16;
    static const int CHUNK_SIZE_Y = 128;
    static const int CHUNK_SIZE_Z = 16;

    unsigned int indexCount;
    int x, y, z;
    Shader shaderProgram;
    VAO vao;
    VBO vbo;
    EBO ebo;
    Block blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
};

#endif