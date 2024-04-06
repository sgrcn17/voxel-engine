#include "block.hpp"

void Block::addVerticesAndIndices(std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    if(id == 0) return;

    GLfloat blockVertices[] = {
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        +0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.03125f, 0.0f,
        -0.5f, -0.5f, +0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.03125f,
        +0.5f, -0.5f, +0.5f,   1.0f, 1.0f, 1.0f,   0.03125f, 0.03125f,
        -0.5f, +0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.03125f, 0.0f,
        +0.5f, +0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.03125f, 0.03125f,
        -0.5f, +0.5f, +0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        +0.5f, +0.5f, +0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.03125f
    };

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

    auto blockData = DataLoader::GetInstance()->GetBlockData(id);
    auto textureX = blockData->textureX;
    auto textureY = blockData->textureY;

    for (int i = 0 ; i < sizeof(blockVertices) / sizeof(float) ; i+=8) {
            blockVertices[i] += x;
            blockVertices[i+1] += y;
            blockVertices[i+2] += z;

            blockVertices[i+6] += textureX;
            blockVertices[i+7] += textureY;
        }

    for (int i = 0 ; i < sizeof(blockIndices) / sizeof(unsigned int) ; i++) {
        blockIndices[i] += vertices.size() / 8;
    }

    vertices.insert(vertices.end(), blockVertices, blockVertices + sizeof(blockVertices) / sizeof(float));
    indices.insert(indices.end(), blockIndices, blockIndices + sizeof(blockIndices) / sizeof(unsigned int));
}