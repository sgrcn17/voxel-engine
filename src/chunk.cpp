#include "chunk.hpp"

Chunk::Chunk(int chunkX, int chunkZ) : x(chunkX), z(chunkZ) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Chunk::~Chunk() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Chunk::UpdateMesh() {
    vertices.clear(); 
    indices.clear();
    
    for(int x = 0 ; x < CHUNK_SIZE ; x++) {
        for(int y = 0 ; y < CHUNK_HEIGHT ; y++) {
            for(int z = 0 ; z < CHUNK_SIZE ; z++) {
                int block = blockID[x + CHUNK_SIZE*y + CHUNK_HEIGHT*CHUNK_SIZE*z];
                if(block == 0) continue;
                
                float fx = static_cast<float>(x) + Chunk::x * CHUNK_SIZE;
                float fy = static_cast<float>(y);
                float fz = static_cast<float>(z) + Chunk::z * CHUNK_SIZE;
                int offset = static_cast<int>(vertices.size() / 5);

                vertices.insert(vertices.end(), {
                    fx + 1, fy + 1, fz, 1.0f, 1.0f,
                    fx + 1, fy,     fz, 1.0f, 0.0f,
                    fx,     fy,     fz, 0.0f, 0.0f,
                    fx,     fy + 1, fz, 0.0f, 1.0f
                });
                indices.insert(indices.end(), {
                    offset + 0, offset + 1, offset + 3,
                    offset + 1, offset + 2, offset + 3  
                });

                vertices.insert(vertices.end(), {
                    fx + 1, fy + 1, fz + 1, 1.0f, 1.0f,
                    fx + 1, fy,     fz + 1, 1.0f, 0.0f,
                    fx,     fy,     fz + 1, 0.0f, 0.0f,
                    fx,     fy + 1, fz + 1, 0.0f, 1.0f
                });
                indices.insert(indices.end(), {
                    offset + 4, offset + 5, offset + 7,
                    offset + 5, offset + 6, offset + 7  
                });

                vertices.insert(vertices.end(), {
                    fx,     fy + 1, fz + 1, 1.0f, 1.0f,
                    fx,     fy + 1, fz,     1.0f, 0.0f,
                    fx,     fy,     fz,     0.0f, 0.0f,
                    fx,     fy,     fz + 1, 0.0f, 1.0f
                });
                indices.insert(indices.end(), {
                    offset + 8,  offset + 9,  offset + 11,
                    offset + 9,  offset + 10, offset + 11  
                });

                vertices.insert(vertices.end(), {
                    fx + 1, fy + 1, fz + 1, 1.0f, 1.0f,
                    fx + 1, fy + 1, fz,     1.0f, 0.0f,
                    fx + 1, fy,     fz,     0.0f, 0.0f,
                    fx + 1, fy,     fz + 1, 0.0f, 1.0f
                });
                indices.insert(indices.end(), {
                    offset + 12, offset + 13, offset + 15,
                    offset + 13, offset + 14, offset + 15  
                });

                vertices.insert(vertices.end(), {
                    fx + 1, fy + 1, fz + 1, 1.0f, 1.0f,
                    fx,     fy + 1, fz + 1, 1.0f, 0.0f,
                    fx,     fy + 1, fz,     0.0f, 0.0f,
                    fx + 1, fy + 1, fz,     0.0f, 1.0f
                });
                indices.insert(indices.end(), {
                    offset + 16, offset + 17, offset + 19,
                    offset + 17, offset + 18, offset + 19  
                });

                vertices.insert(vertices.end(), {
                    fx + 1, fy,     fz + 1, 1.0f, 1.0f,
                    fx,     fy,     fz + 1, 1.0f, 0.0f,
                    fx,     fy,     fz,     0.0f, 0.0f,
                    fx + 1, fy,     fz,     0.0f, 1.0f
                });
                indices.insert(indices.end(), {
                    offset + 20, offset + 21, offset + 23,
                    offset + 21, offset + 22, offset + 23  
                });
            }
        }
    }
}

void Chunk::Draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}