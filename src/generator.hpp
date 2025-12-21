#pragma once

#include <cmath>
#include <algorithm>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include "data.hpp"

struct ChunkData;

inline float fractalNoise(float x, float z, int octaves = 4) {
    float value = 0.0f;
    float amplitude = 1.0f;
    float frequency = 0.01f; 
    float maxValue = 0.0f;
    
    glm::vec2 position(x, z);
    
    for(int i = 0; i < octaves; i++) {
        float noise = glm::perlin(position * frequency);
        noise = (noise + 1.0f) * 0.5f;
        
        value += noise * amplitude;
        maxValue += amplitude;
        amplitude *= 0.5f;
        frequency *= 2.0f;
    }
    
    return value / maxValue;
}

inline void GenerateHeightMap(int chunkX, int chunkZ, std::array<unsigned short, CHUNK_SIZE * CHUNK_SIZE>& heightMap) {
    const int worldXBase = chunkX * CHUNK_SIZE;
    const int worldZBase = chunkZ * CHUNK_SIZE;
    const int baseHeight = 64;
    const int heightRange = 30;
    
    for(int z = 0; z < CHUNK_SIZE; z++) {
        for(int x = 0; x < CHUNK_SIZE; x++) {
            const int worldX = worldXBase + x;
            const int worldZ = worldZBase + z;
            
            float noiseValue = fractalNoise(static_cast<float>(worldX), static_cast<float>(worldZ), 4);
            int height = baseHeight + static_cast<int>(noiseValue * heightRange);
            height = std::clamp(height, 0, CHUNK_HEIGHT - 1);
            
            heightMap[x + CHUNK_SIZE * z] = height;
        }
    }
}

inline void GenerateChunkBlocks(int chunkX, int chunkZ, ChunkData& data) {
    std::array<unsigned short, CHUNK_SIZE * CHUNK_SIZE> heightMap; 
    GenerateHeightMap(chunkX, chunkZ, heightMap);

    for(int x = 0; x < CHUNK_SIZE; x++) {
        for(int z = 0; z < CHUNK_SIZE; z++) {
            const int terrainHeight = heightMap[x + CHUNK_SIZE * z];
            
            for(int y = 0; y < CHUNK_HEIGHT; y++) {
                const int blockIndex = x + CHUNK_SIZE * y + CHUNK_SIZE * CHUNK_HEIGHT * z;
                
                if(y > terrainHeight) {
                    data.blockID[blockIndex] = static_cast<unsigned short>(BlockType::Air);
                } else if(y == terrainHeight) {
                    data.blockID[blockIndex] = static_cast<unsigned short>(BlockType::Grass);
                } else if(y >= terrainHeight - 3) {
                    data.blockID[blockIndex] = static_cast<unsigned short>(BlockType::Dirt);
                } else {
                    data.blockID[blockIndex] = static_cast<unsigned short>(BlockType::Stone);
                }
            }
        }
    }
}

