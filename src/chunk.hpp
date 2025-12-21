#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include <vector>
#include <memory>
#include <map>
#include <utility>
#include <future>

#include "data.hpp"
#include "thread_pool.hpp"

struct ChunkData {
    std::array<unsigned short, CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE> blockID;
    int chunkX, chunkZ;
    std::array<ChunkData*, static_cast<size_t>(ChunkNeighbour::SIZE)> neighbors{};
};

struct ChunkMesh {
    std::vector<float> vertices;
    std::vector<unsigned short> indices;

    unsigned int VBO, VAO, EBO;
};

struct ChunkCache {
    std::map<std::pair<int, int>, std::shared_ptr<ChunkData>> chunkData;
    std::array<std::shared_ptr<ChunkData>, WORLD_SIZE * WORLD_SIZE> cachedData;
    std::array<std::shared_ptr<ChunkMesh>, WORLD_SIZE * WORLD_SIZE> cachedMeshes;
    std::array<ChunkState, WORLD_SIZE * WORLD_SIZE> chunkStates{};
    
    std::unique_ptr<ThreadPool> threadPool;
    std::map<size_t, std::future<void>> pendingMeshUpdates;
    std::map<std::pair<int, int>, std::future<void>> pendingChunkGenerations;
};

namespace Chunk {
    void InitCache(ChunkCache& cache);
    void InitChunkMesh(ChunkMesh& mesh);
    void DestroyChunkMesh(ChunkMesh& mesh);
    
    std::shared_ptr<ChunkData> GetChunkData(ChunkCache& cache, int x, int z);
    int GetBlockId(ChunkCache& cache, int worldX, int worldY, int worldZ);
    void GenerateChunk(ChunkCache& cache, int chunkX, int chunkZ);
    
    void UpdateCache(ChunkCache& cache, int centerChunkX, int centerChunkZ);
    void ProcessChunks(ChunkCache& cache, int centerChunkX, int centerChunkZ);
    
    void UpdateMesh(ChunkMesh& mesh, ChunkData& data);
    void UpdateMeshData(ChunkMesh& mesh, ChunkData& data); 
    void UploadMeshToGPU(ChunkMesh& mesh); 
    void Draw(ChunkMesh& mesh);
};
