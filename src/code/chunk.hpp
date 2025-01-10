#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "vao.hpp"
#include "vbo.hpp"
#include "ebo.hpp"
#include "model.hpp"
#include <vector>

const unsigned int CHUNK_SIZE = 16, CHUNK_HEIGHT = 256;

class Chunk {
    public:
    Chunk(int x, int z, int data[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]);

    void Render();
    bool isSolid(int i, int j, int k) { return blockIds[i][j][k] != 0; }

    void AddBlock(int i, int j, int k, int id);
    void RemoveBlock(int i, int j, int k);

    private:
    void EmplaceBlockRenderData(int i, int j, int k, std::vector<GLfloat>& _vertices, std::vector<GLuint>& _indices);
    void UpdateMesh();
    void UpdateBuffers();

    int x, z;
    int blockIds[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    VAO* vao;
    VBO* vbo;
    EBO* ebo;
};