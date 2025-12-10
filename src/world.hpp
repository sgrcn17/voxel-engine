#pragma once

#include <map>
#include <functional>
#include <utility>
#include <array>
#include <memory>
#include <filesystem>

#include "chunk.hpp"

struct World {
    void UpdateChunks(int centerChunkX, int centerChunkZ);
    void Render();

    std::shared_ptr<Chunk> GetChunk(int x, int z);
    int GetBlockId(int worldX, int worldY, int worldZ);
    void GenerateChunk(int chunkX, int chunkZ);

    static World* GetInstance();

    private:
    static World* instance;

    std::map<std::pair<int, int>, std::shared_ptr<Chunk>> chunks;
    std::array<std::shared_ptr<Chunk>, WORLD_SIZE * WORLD_SIZE> loadedChunks;
};

