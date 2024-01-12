#include "chunk.hpp"

GLuint indices1[] = {
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

//      coordinates       //        color       //      texture coords
GLfloat vertices1[] = {
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f
};

Chunk::Chunk(int x, int y, int z, const Shader& shaderProgram)
    : x(x), y(y), z(z), shaderProgram(shaderProgram), 
      vbo(vertices1, sizeof(vertices1)), ebo(indices1, sizeof(indices1)) // Inicjalizacja VBO i EBO z null i 0
{
    // Inicjalizacja bloków
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        for (int j = 0; j < CHUNK_SIZE; ++j) {
            for (int k = 0; k < CHUNK_SIZE; ++k) {
                // Generowanie bloku na podstawie współrzędnych
                blocks[i][j][k] = Block(i + x, j + y, k + z);
            }
        }
    }

    // Generowanie vertexów i indeksów na podstawie bloków
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        for (int j = 0; j < CHUNK_SIZE; ++j) {
            for (int k = 0; k < CHUNK_SIZE; ++k) {
                // Dodawanie vertexów i indeksów dla danego bloku do vectorsów
                blocks[i][j][k].addVerticesAndIndices(vertices, indices);
            }
        }
    }

    // Przypisanie danych do VBO i EBO
    vao.Bind();
    vbo = VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = EBO(indices.data(), indices.size() * sizeof(unsigned int));
    indexCount = indices.size();  // Aktualizuj indexCount

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8*sizeof(float), (void*)(6*sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Chunk::Draw() {
    shaderProgram.Activate();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}