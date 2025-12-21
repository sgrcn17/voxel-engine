#include "chunk.hpp"
#include "generator.hpp"
#include "uv_lookup.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>
#include <unordered_set>
#include <array>
#include <future>
#include <chrono>
#include <thread>

void Chunk::InitChunkMesh(ChunkMesh& mesh) {
    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glGenBuffers(1, &mesh.EBO);

    glBindVertexArray(mesh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Chunk::DestroyChunkMesh(ChunkMesh& mesh) {
    glDeleteVertexArrays(1, &mesh.VAO);
    glDeleteBuffers(1, &mesh.VBO);
    glDeleteBuffers(1, &mesh.EBO);
}

void Chunk::InitCache(ChunkCache& cache) {
    size_t numThreads = std::max(1u, std::thread::hardware_concurrency() - 1);
    cache.threadPool = std::make_unique<ThreadPool>(numThreads);
    
    for(size_t i = 0; i < cache.cachedMeshes.size(); ++i) {
        cache.cachedMeshes[i] = std::make_shared<ChunkMesh>();
        cache.cachedData[i] = std::make_shared<ChunkData>();
        cache.chunkStates[i] = ChunkState::Free;
        InitChunkMesh(*cache.cachedMeshes[i]);
    }
}

void Chunk::UpdateCache(ChunkCache& cache, int centerChunkX, int centerChunkZ) {
    int halfWorldSize = WORLD_SIZE / 2;
    
    struct PairHash {
        std::size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };
    
    auto inRange = [](int x, int z, int centerX, int centerZ, int halfWorldSize) {
        return x >= centerX - halfWorldSize && x < centerX + halfWorldSize && z >= centerZ - halfWorldSize && z < centerZ + halfWorldSize;
    };

    std::unordered_set<std::pair<int, int>, PairHash> loadedChunks;
    std::vector<std::pair<int, int>> updatedChunks;
    std::queue<size_t> freeIndexes;
    for(size_t index = 0; index < cache.cachedData.size(); ++index) {
        if(cache.chunkStates[index] != ChunkState::Free && inRange(cache.cachedData[index]->chunkX, cache.cachedData[index]->chunkZ, centerChunkX, centerChunkZ, halfWorldSize)) {
            loadedChunks.insert({cache.cachedData[index]->chunkX, cache.cachedData[index]->chunkZ});
        } else {
            freeIndexes.push(index);
            updatedChunks.push_back({cache.cachedData[index]->chunkX, cache.cachedData[index]->chunkZ});
        }
    }

    for(int x = centerChunkX - halfWorldSize; x < centerChunkX + halfWorldSize; ++x) {
        for(int z = centerChunkZ - halfWorldSize; z < centerChunkZ + halfWorldSize; ++z) {
            if(loadedChunks.find({x, z}) != loadedChunks.end()) continue;
            auto chunkData = GetChunkData(cache, x, z);
            if(!freeIndexes.empty()) {
                cache.cachedData[freeIndexes.front()] = chunkData;
                cache.chunkStates[freeIndexes.front()] = ChunkState::UpdatedData;
                updatedChunks.push_back({x, z});
                freeIndexes.pop();
            }
        }
    }
    
    std::vector<std::pair<int, int>> df = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::unordered_set<std::pair<int, int>, PairHash> toUpdate;
    for(const auto& chunk : updatedChunks) {
        for(const auto& direction : df) {
            int newX = chunk.first + direction.first;
            int newZ = chunk.second + direction.second;
            if(loadedChunks.find({newX, newZ}) == loadedChunks.end()) continue;
            toUpdate.insert({newX, newZ});
        }
    }

    for(int index = 0; index < cache.cachedData.size(); ++index) {
        if(toUpdate.find({cache.cachedData[index]->chunkX, cache.cachedData[index]->chunkZ}) == toUpdate.end()) continue;
        cache.chunkStates[index] = ChunkState::UpdatedData;
    }
}

void Chunk::ProcessChunks(ChunkCache& cache, int centerChunkX, int centerChunkZ) {
    Chunk::UpdateCache(cache, centerChunkX, centerChunkZ);
    
    for(size_t index = 0; index < cache.cachedData.size(); ++index) {
        ChunkData* chunkData = cache.cachedData[index].get();
        chunkData->neighbors[static_cast<size_t>(ChunkNeighbour::West)] = Chunk::GetChunkData(cache, chunkData->chunkX - 1, chunkData->chunkZ).get();
        chunkData->neighbors[static_cast<size_t>(ChunkNeighbour::East)] = Chunk::GetChunkData(cache, chunkData->chunkX + 1, chunkData->chunkZ).get();
        chunkData->neighbors[static_cast<size_t>(ChunkNeighbour::North)] = Chunk::GetChunkData(cache, chunkData->chunkX, chunkData->chunkZ - 1).get();
        chunkData->neighbors[static_cast<size_t>(ChunkNeighbour::South)] = Chunk::GetChunkData(cache, chunkData->chunkX, chunkData->chunkZ + 1).get();
    }
    
    for(size_t index = 0; index < cache.cachedMeshes.size(); ++index) {
        if(cache.chunkStates[index] == ChunkState::UpdatedData) {
            if(cache.pendingMeshUpdates.find(index) == cache.pendingMeshUpdates.end()) {
                auto mesh = cache.cachedMeshes[index];
                auto data = cache.cachedData[index];
                
                auto promise = std::make_shared<std::promise<void>>();
                cache.pendingMeshUpdates[index] = promise->get_future();
                
                cache.threadPool->enqueue([mesh, data, promise]() {
                    Chunk::UpdateMeshData(*mesh, *data);
                    promise->set_value();
                });
            }
        }
    }
    
    auto it = cache.pendingMeshUpdates.begin();
    while(it != cache.pendingMeshUpdates.end()) {
        if(it->second.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            size_t index = it->first;
            Chunk::UploadMeshToGPU(*cache.cachedMeshes[index]);
            cache.chunkStates[index] = ChunkState::UpdatedMesh;
            it = cache.pendingMeshUpdates.erase(it);
        } else {
            ++it;
        }
    }
    
    auto chunkIt = cache.pendingChunkGenerations.begin();
    while(chunkIt != cache.pendingChunkGenerations.end()) {
        if(chunkIt->second.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            chunkIt = cache.pendingChunkGenerations.erase(chunkIt);
        } else {
            ++chunkIt;
        }
    }
    
    for(size_t index = 0; index < cache.cachedMeshes.size(); ++index) {
        if(cache.chunkStates[index] == ChunkState::UpdatedMesh) {
            Chunk::Draw(*cache.cachedMeshes[index]);
        }
    }
}
std::shared_ptr<ChunkData> Chunk::GetChunkData(ChunkCache& cache, int x, int z) {
    std::pair<int, int> key = std::make_pair(x, z);
    auto it = cache.chunkData.find(key);
    
    if (it != cache.chunkData.end()) {
        return it->second;
    }
    
    auto pendingIt = cache.pendingChunkGenerations.find(key);
    if (pendingIt != cache.pendingChunkGenerations.end()) {
        pendingIt->second.wait();
        it = cache.chunkData.find(key);
        if (it != cache.chunkData.end()) {
            return it->second;
        }
    }
    
    auto promise = std::make_shared<std::promise<void>>();
    cache.pendingChunkGenerations[key] = promise->get_future();
    
    cache.threadPool->enqueue([&cache, x, z, promise]() {
        Chunk::GenerateChunk(cache, x, z);
        promise->set_value();
    });
    
    cache.pendingChunkGenerations[key].wait();
    
    it = cache.chunkData.find(key);
    return it->second;
}

void Chunk::GenerateChunk(ChunkCache& cache, int chunkX, int chunkZ) {
    auto chunkData = std::make_shared<ChunkData>();
    chunkData->chunkX = chunkX;
    chunkData->chunkZ = chunkZ;
    
    cache.chunkData[{chunkX, chunkZ}] = chunkData;
    
    GenerateChunkBlocks(chunkX, chunkZ, *chunkData);
}

inline void AddQuadVertices(std::vector<float>& vertices, 
    float x0, float y0, float z0, float x1, float y1, float z1,
    float x2, float y2, float z2, float x3, float y3, float z3,
    int texX, int texY) {
    
    vertices.push_back(x0); vertices.push_back(y0); vertices.push_back(z0); 
    vertices.push_back(GetEncodedUV(texX, texY, 0)); 
    
    vertices.push_back(x1); vertices.push_back(y1); vertices.push_back(z1); 
    vertices.push_back(GetEncodedUV(texX, texY, 1));
    
    vertices.push_back(x2); vertices.push_back(y2); vertices.push_back(z2); 
    vertices.push_back(GetEncodedUV(texX, texY, 2)); 
    
    vertices.push_back(x3); vertices.push_back(y3); vertices.push_back(z3); 
    vertices.push_back(GetEncodedUV(texX, texY, 3)); 
}

inline void AddQuadIndices(std::vector<unsigned short>& indices, unsigned short offset) {
    indices.push_back(static_cast<unsigned short>(offset + 0));
    indices.push_back(static_cast<unsigned short>(offset + 1));
    indices.push_back(static_cast<unsigned short>(offset + 3));
    indices.push_back(static_cast<unsigned short>(offset + 1));
    indices.push_back(static_cast<unsigned short>(offset + 2));
    indices.push_back(static_cast<unsigned short>(offset + 3));
}

inline int GetBlockInNeighborChunk(ChunkData* neighbor, int localX, int localY, int localZ) {
    if(neighbor == nullptr || 
       localY < 0 || localY >= CHUNK_HEIGHT ||
       localX < 0 || localX >= CHUNK_SIZE ||
       localZ < 0 || localZ >= CHUNK_SIZE) {
        return 0;
    }
    const int blockIndex = localX + CHUNK_SIZE * localY + CHUNK_SIZE * CHUNK_HEIGHT * localZ;
    return neighbor->blockID[blockIndex];
}

void Chunk::UpdateMeshData(ChunkMesh& mesh, ChunkData& data) {
    mesh.vertices.resize(0);
    mesh.indices.resize(0);
    
    const size_t maxVertices = CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 6 * 4 * 4;
    const size_t maxIndices = CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 6 * 6;
    
    if(mesh.vertices.capacity() < maxVertices) {
        mesh.vertices.reserve(maxVertices);
    }
    if(mesh.indices.capacity() < maxIndices) {
        mesh.indices.reserve(maxIndices);
    }
    
    int worldXBase = data.chunkX * CHUNK_SIZE;
    int worldZBase = data.chunkZ * CHUNK_SIZE;

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
                const unsigned short blockID = data.blockID[blockIndex];
                if(blockID == 0) continue;
                
                BlockType blockType = static_cast<BlockType>(blockID);
                if(blockType >= BlockType::SIZE) blockType = BlockType::Stone;
                
                const float fz = static_cast<float>(z) + worldZBase;

                auto getTexCoords = [](TextureIndex textureIndex) -> std::pair<int, int> {
                    TextureData texData = GetTextureData(textureIndex);
                    return {texData.x, texData.y};
                };

                // Front face (NEG_Z)
                bool frontFaceVisible = false;
                if(z == 0) {
                    ChunkData* neighbor = data.neighbors[static_cast<size_t>(ChunkNeighbour::North)];
                    int neighborBlock = GetBlockInNeighborChunk(neighbor, x, y, CHUNK_SIZE - 1);
                    frontFaceVisible = (neighborBlock == 0);
                } else {
                    frontFaceVisible = (data.blockID[blockIndex - chunkSizeZ] == 0);
                }
                if(frontFaceVisible) {
                    auto [texX, texY] = getTexCoords(GetBlockTexture(blockType, FaceDirection::Front));
                    unsigned short offset = static_cast<unsigned short>(mesh.vertices.size() / 4);
                    AddQuadVertices(mesh.vertices, 
                        fx,     fy,     fz,
                        fx + 1, fy,     fz,
                        fx + 1, fy + 1, fz,
                        fx,     fy + 1, fz,
                        texX, texY
                    );
                    AddQuadIndices(mesh.indices, offset);
                } 
                
                // Back face (POS_Z)
                bool backFaceVisible = false;
                if(z == CHUNK_SIZE - 1) {
                    ChunkData* neighbor = data.neighbors[static_cast<size_t>(ChunkNeighbour::South)];
                    int neighborBlock = GetBlockInNeighborChunk(neighbor, x, y, 0);
                    backFaceVisible = (neighborBlock == 0);
                } else {
                    backFaceVisible = (data.blockID[blockIndex + chunkSizeZ] == 0);
                }
                if(backFaceVisible) {
                    auto [texX, texY] = getTexCoords(GetBlockTexture(blockType, FaceDirection::Back));
                    unsigned short offset = static_cast<unsigned short>(mesh.vertices.size() / 4);
                    AddQuadVertices(mesh.vertices,
                        fx,     fy,     fz + 1,
                        fx + 1, fy,     fz + 1,
                        fx + 1, fy + 1, fz + 1,
                        fx,     fy + 1, fz + 1,
                        texX, texY
                    );
                    AddQuadIndices(mesh.indices, offset);
                }

                // Left face (NEG_X)
                bool leftFaceVisible = false;
                if(x == 0) {
                    ChunkData* neighbor = data.neighbors[static_cast<size_t>(ChunkNeighbour::West)];
                    int neighborBlock = GetBlockInNeighborChunk(neighbor, CHUNK_SIZE - 1, y, z);
                    leftFaceVisible = (neighborBlock == 0);
                } else {
                    leftFaceVisible = (data.blockID[blockIndex - 1] == 0);
                }
                if(leftFaceVisible) {
                    auto [texX, texY] = getTexCoords(GetBlockTexture(blockType, FaceDirection::Left));
                    unsigned short offset = static_cast<unsigned short>(mesh.vertices.size() / 4);
                    AddQuadVertices(mesh.vertices,
                        fx,     fy,     fz,
                        fx,     fy,     fz + 1,
                        fx,     fy + 1, fz + 1,
                        fx,     fy + 1, fz,
                        texX, texY
                    );
                    AddQuadIndices(mesh.indices, offset);
                }

                // Right face (POS_X)
                bool rightFaceVisible = false;
                if(x == CHUNK_SIZE - 1) {
                    ChunkData* neighbor = data.neighbors[static_cast<size_t>(ChunkNeighbour::East)];
                    int neighborBlock = GetBlockInNeighborChunk(neighbor, 0, y, z);
                    rightFaceVisible = (neighborBlock == 0);
                } else {
                    rightFaceVisible = (data.blockID[blockIndex + 1] == 0);
                }
                if(rightFaceVisible) {
                    auto [texX, texY] = getTexCoords(GetBlockTexture(blockType, FaceDirection::Right));
                    unsigned short offset = static_cast<unsigned short>(mesh.vertices.size() / 4);
                    AddQuadVertices(mesh.vertices,
                        fx + 1, fy,     fz + 1,
                        fx + 1, fy,     fz,
                        fx + 1, fy + 1, fz,
                        fx + 1, fy + 1, fz + 1,
                        texX, texY
                    );
                    AddQuadIndices(mesh.indices, offset);
                }

                // Top face (POS_Y)
                if(y == CHUNK_HEIGHT - 1 || data.blockID[blockIndex + CHUNK_SIZE] == 0) {
                    auto [texX, texY] = getTexCoords(GetBlockTexture(blockType, FaceDirection::Top));
                    unsigned short offset = static_cast<unsigned short>(mesh.vertices.size() / 4);
                    AddQuadVertices(mesh.vertices,
                        fx,     fy + 1, fz,
                        fx + 1, fy + 1, fz,
                        fx + 1, fy + 1, fz + 1,
                        fx,     fy + 1, fz + 1,
                        texX, texY
                    );
                    AddQuadIndices(mesh.indices, offset);
                }

                // Bottom face (NEG_Y)
                if(y == 0 || data.blockID[blockIndex - CHUNK_SIZE] == 0) {
                    auto [texX, texY] = getTexCoords(GetBlockTexture(blockType, FaceDirection::Bottom));
                    unsigned short offset = static_cast<unsigned short>(mesh.vertices.size() / 4);
                    AddQuadVertices(mesh.vertices,
                        fx,     fy,     fz + 1,
                        fx + 1, fy,     fz + 1,
                        fx + 1, fy,     fz,
                        fx,     fy,     fz,
                        texX, texY
                    );
                    AddQuadIndices(mesh.indices, offset);
                }   
            }
        }
    }
}

void Chunk::UploadMeshToGPU(ChunkMesh& mesh) {
    glBindVertexArray(mesh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);
}

void Chunk::UpdateMesh(ChunkMesh& mesh, ChunkData& data) {
    UpdateMeshData(mesh, data);
    UploadMeshToGPU(mesh);
}

void Chunk::Draw(ChunkMesh& mesh) {
    if(mesh.indices.empty()) return;
    
    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_SHORT, 0);
}