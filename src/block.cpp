#include "block.hpp"

Block::Block(int x, int y, int z) : x(x), y(y), z(z) {}

void Block::addVerticesAndIndices(std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    // Wierzchołki dla bloku na pozycji (x, y, z)
    GLfloat blockVertices[] = {
        x-0.5f, y-0.5f, z-0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        x+0.5f, y-0.5f, z-0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        x-0.5f, y-0.5f, z+0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
        x+0.5f, y-0.5f, z+0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        x-0.5f, y+0.5f, z-0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        x+0.5f, y+0.5f, z-0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        x-0.5f, y+0.5f, z+0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        x+0.5f, y+0.5f, z+0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };

    // Indeksy dla bloku
    GLuint blockIndices[] = {
        0, 2, 3, //bottom
        1, 0, 3,
        0, 4, 5, //front
        1, 0, 5,
        2, 6, 4, //left
        0, 2, 4,
        1, 5, 7, //right
        3, 1, 7,
        3, 7, 6, //back
        2, 3, 6,
        4, 6, 7, //top
        5, 4, 7
    };

    for (int i = 0 ; i < sizeof(blockIndices) / sizeof(unsigned int) ; i++) {
        blockIndices[i] += vertices.size() / 8;
    }

    // Dodawanie wierzchołków i indeksów do vectorsów
    vertices.insert(vertices.end(), blockVertices, blockVertices + sizeof(blockVertices) / sizeof(float));
    indices.insert(indices.end(), blockIndices, blockIndices + sizeof(blockIndices) / sizeof(unsigned int));
}