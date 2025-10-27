#pragma once

#include <map>
#include <utility>

#include "chunk.hpp"

struct World {
    Chunk& GetChunk(int x, int z) {
        pair<int, int> key = make_pair(x, z);
        if (chunks.find(key) == chunks.end()) {
            GenerateChunk(x, z);
        }
        return chunks[key];
    }

    void GenerateChunk(int chunkX, int chunkZ);

    std::map<std::pair<int, int>, Chunk> chunks;
    std::array<Chunk, WORLD_SIZE * WORLD_SIZE> loadedChunks;
};

World world;

void Render();

