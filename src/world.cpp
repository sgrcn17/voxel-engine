#include "world.hpp"

void World::GenerateChunk(int chunkX, int chunkZ) {
    world.chunks[make_pair(chunkX, chunkZ)] = Chunk();
}

void Render() {
    for(auto& chunk : world.loadedChunks) {
        chunk.Draw();
    }
}