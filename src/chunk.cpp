#include "chunk.hpp"
#include "world.hpp"
#include "generator.hpp"

Chunk::Chunk(int chunkX, int chunkZ) : x(chunkX), z(chunkZ) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    std::array<unsigned short, CHUNK_SIZE * CHUNK_SIZE> heightMap;
    GenerateHeightMap(x, z, heightMap);
    GenerateChunkBlocks(heightMap, blockID);
    
    UpdateMesh();
}

Chunk::~Chunk() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


inline void AddQuadVertices(std::vector<float>& vertices, 
    float x0, float y0, float z0, float x1, float y1, float z1,
    float x2, float y2, float z2, float x3, float y3, float z3) {
    vertices.push_back(x0); vertices.push_back(y0); vertices.push_back(z0); vertices.push_back(1.0f); vertices.push_back(1.0f);
    vertices.push_back(x1); vertices.push_back(y1); vertices.push_back(z1); vertices.push_back(1.0f); vertices.push_back(0.0f);
    vertices.push_back(x2); vertices.push_back(y2); vertices.push_back(z2); vertices.push_back(0.0f); vertices.push_back(0.0f);
    vertices.push_back(x3); vertices.push_back(y3); vertices.push_back(z3); vertices.push_back(0.0f); vertices.push_back(1.0f);
}

inline void AddQuadIndices(std::vector<unsigned short>& indices, unsigned short offset) {
    indices.push_back(static_cast<unsigned short>(offset + 0));
    indices.push_back(static_cast<unsigned short>(offset + 1));
    indices.push_back(static_cast<unsigned short>(offset + 3));
    indices.push_back(static_cast<unsigned short>(offset + 1));
    indices.push_back(static_cast<unsigned short>(offset + 2));
    indices.push_back(static_cast<unsigned short>(offset + 3));
}

void Chunk::UpdateMesh() {
    vertices.clear(); 
    indices.clear();
    
    const size_t maxVertices = CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 6 * 4 * 5;
    const size_t maxIndices = CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 6 * 6;
    vertices.reserve(maxVertices);
    indices.reserve(maxIndices);
    
    int worldXBase = Chunk::x * CHUNK_SIZE;
    int worldZBase = Chunk::z * CHUNK_SIZE;

    const int chunkSizeZ = CHUNK_HEIGHT * CHUNK_SIZE;
    
    for(int x = 0 ; x < CHUNK_SIZE ; x++) {
        const float fx = static_cast<float>(x) + worldXBase;
        const int worldX = x + worldXBase;
        
        for(int y = 0 ; y < CHUNK_HEIGHT ; y++) {
            const int yOffset = CHUNK_SIZE * y;
            const float fy = static_cast<float>(y);
            const int worldY = y;
            
            for(int z = 0 ; z < CHUNK_SIZE ; z++) {
                const int blockIndex = x + yOffset + chunkSizeZ * z;
                const int block = blockID[blockIndex];
                if(block == 0) continue;
                
                const float fz = static_cast<float>(z) + worldZBase;
                const int worldZ = z + worldZBase;

                bool render;

                if(z <= 0) render = (World::GetInstance()->GetBlockId(worldX, worldY, worldZ - 1) == 0);
                else render = (blockID[blockIndex - chunkSizeZ] == 0);

                if(render) {
                    unsigned short offset = static_cast<unsigned short>(vertices.size() / 5);
                    AddQuadVertices(vertices, 
                        fx + 1, fy + 1, fz,
                        fx + 1, fy,     fz,
                        fx,     fy,     fz,
                        fx,     fy + 1, fz
                    );
                    AddQuadIndices(indices, offset);
                } 
                
                if(z >= CHUNK_SIZE - 1) render = (World::GetInstance()->GetBlockId(worldX, worldY, worldZ + 1) == 0);
                else render = (blockID[blockIndex + chunkSizeZ] == 0);

                if(render) {
                    unsigned short offset = static_cast<unsigned short>(vertices.size() / 5);
                    AddQuadVertices(vertices,
                        fx + 1, fy + 1, fz + 1,
                        fx + 1, fy,     fz + 1,
                        fx,     fy,     fz + 1,
                        fx,     fy + 1, fz + 1
                    );
                    AddQuadIndices(indices, offset);
                }

                if(x <= 0) render = (World::GetInstance()->GetBlockId(worldX - 1, worldY, worldZ) == 0);
                else render = (blockID[blockIndex - 1] == 0);

                if(render) {
                    unsigned short offset = static_cast<unsigned short>(vertices.size() / 5);
                    AddQuadVertices(vertices,
                        fx,     fy + 1, fz + 1,
                        fx,     fy,     fz + 1,
                        fx,     fy,     fz,
                        fx,     fy + 1, fz
                    );
                    AddQuadIndices(indices, offset);
                }

                if(x >= CHUNK_SIZE - 1) render = (World::GetInstance()->GetBlockId(worldX + 1, worldY, worldZ) == 0);
                else render = (blockID[blockIndex + 1] == 0);

                if(render) {
                    unsigned short offset = static_cast<unsigned short>(vertices.size() / 5);
                    AddQuadVertices(vertices,
                        fx + 1, fy + 1, fz + 1,
                        fx + 1, fy,     fz + 1,
                        fx + 1, fy,     fz,
                        fx + 1, fy + 1, fz
                    );
                    AddQuadIndices(indices, offset);
                }

                if(y == CHUNK_HEIGHT - 1 || blockID[blockIndex + CHUNK_SIZE] == 0) {
                    unsigned short offset = static_cast<unsigned short>(vertices.size() / 5);
                    AddQuadVertices(vertices,
                        fx + 1, fy + 1, fz + 1,
                        fx,     fy + 1, fz + 1,
                        fx,     fy + 1, fz,
                        fx + 1, fy + 1, fz
                    );
                    AddQuadIndices(indices, offset);
                }

                if(y == 0 || blockID[blockIndex - CHUNK_SIZE] == 0) {
                    unsigned short offset = static_cast<unsigned short>(vertices.size() / 5);
                    AddQuadVertices(vertices,
                        fx + 1, fy,     fz + 1,
                        fx,     fy,     fz + 1,
                        fx,     fy,     fz,
                        fx + 1, fy,     fz
                    );
                    AddQuadIndices(indices, offset);
                }   
            }
        }
    }

    updated = true;

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

void Chunk::Draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);
}
