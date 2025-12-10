#include "world.hpp"
#include "generator.hpp"
#include "chunk.hpp"

World* World::instance = nullptr;

World* World::GetInstance() {
    if (instance == nullptr) {
        instance = new World();
    }
    return instance;
}

void World::GenerateChunk(int chunkX, int chunkZ) {
    World::chunks[{chunkX, chunkZ}] = std::make_shared<Chunk>(chunkX, chunkZ);
}

std::shared_ptr<Chunk> World::GetChunk(int x, int z) {
    std::pair<int, int> key = std::make_pair(x, z);
    if (chunks.find(key) == chunks.end()) {
        GenerateChunk(x, z);
    }
    return chunks[key];
}

int World::GetBlockId(int worldX, int worldY, int worldZ) {
    if(worldY < 0 || worldY >= CHUNK_HEIGHT) {
        return 1;
    }
    int chunkX = (worldX >= 0) ? (worldX / CHUNK_SIZE) : ((worldX - CHUNK_SIZE + 1) / CHUNK_SIZE);
    int chunkZ = (worldZ >= 0) ? (worldZ / CHUNK_SIZE) : ((worldZ - CHUNK_SIZE + 1) / CHUNK_SIZE);
   
    auto chunkIt = chunks.find({chunkX, chunkZ});
    if (chunkIt == chunks.end()) {
        return 0;
    }

    std::shared_ptr<Chunk> chunk = chunkIt->second;
    
    int localX = ((worldX % CHUNK_SIZE) + CHUNK_SIZE) % CHUNK_SIZE;
    int localY = worldY;
    int localZ = ((worldZ % CHUNK_SIZE) + CHUNK_SIZE) % CHUNK_SIZE; 
    
    return chunk->blockID[localX + CHUNK_SIZE * localY + CHUNK_HEIGHT * CHUNK_SIZE * localZ];
}

void World::UpdateChunks(int centerChunkX, int centerChunkZ) {
    int halfWorldSize = WORLD_SIZE / 2;
    int index = 0;

    for(int z = centerChunkZ - halfWorldSize; z < centerChunkZ + halfWorldSize; ++z) {
        for(int x = centerChunkX - halfWorldSize; x < centerChunkX + halfWorldSize; ++x) {
            auto chunk = GetChunk(x, z);
            World::loadedChunks[index++] = chunk;
            
            if(chunk->updated) continue;
            chunk->UpdateMesh();
        }
    }
}

void World::Render() {
    for(auto& chunk : World::loadedChunks) {
        chunk->Draw();
    }
}