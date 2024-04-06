#include "chunk.hpp"

Chunk::Chunk(int x, int y, int z, const Shader& shaderProgram)
    : x(x), y(y), z(z), shaderProgram(shaderProgram), 
      vbo(nullptr, 0), ebo(nullptr, 0)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < CHUNK_SIZE_X; ++i) {
        for (int j = 0; j < CHUNK_SIZE_Y; ++j) {
            for (int k = 0; k < CHUNK_SIZE_Z; ++k) {
                blocks[i][j][k] = Block(i+x, j+y, k+z, (j > 40) ? 0 : 1);
                blocks[i][j][k].addVerticesAndIndices(vertices, indices);
            }
        }
    }

    vao.Bind();
    vbo = VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = EBO(indices.data(), indices.size() * sizeof(unsigned int));
    indexCount = indices.size();

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8*sizeof(float), (void*)(6*sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Chunk::UpdateMesh() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < CHUNK_SIZE_X; ++i) {
        for (int j = 0; j < CHUNK_SIZE_Y; ++j) {
            for (int k = 0; k < CHUNK_SIZE_Z; ++k) {
                blocks[i][j][k].addVerticesAndIndices(vertices, indices);
            }
        }
    }

    vao.Bind();
    vbo.Update(vertices.data(), vertices.size() * sizeof(float));
    ebo.Update(indices.data(), indices.size() * sizeof(unsigned int));
    indexCount = indices.size();
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

}

void Chunk::RemoveBlock(int x, int y, int z) {
    blocks[x][y][z] = Block(x, y, z, 0);
    UpdateMesh();
}

void Chunk::Draw() {
    shaderProgram.Activate();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}