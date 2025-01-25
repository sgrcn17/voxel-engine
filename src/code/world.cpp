#include "world.hpp"

void World::Update() {
    
}

void World::CreateChunk(int x, int z) {
    std::cout << "Creating chunk " << x << " " << z << std::endl;

    int data[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];

    for(int i = 0; i < CHUNK_SIZE; i++) {
        for(int j = 0; j < CHUNK_HEIGHT; j++) {
            for(int k = 0; k < CHUNK_SIZE; k++) {
                data[i][j][k] = 0;
                int height = static_cast<int>(GenerateHeight(i + x*CHUNK_SIZE, k + z*CHUNK_SIZE));
                if(j <= height-5) {
                    data[i][j][k] = 3;
                } else if(j <= height-1) {
                    data[i][j][k] = 1;
                } else if(j == height) {
                    data[i][j][k] = 2;
                }
            }
        }
    }

    chunks[x][z] = new Chunk(16*x, 16*z, data);
}

void World::Render() {
    for(auto& x : chunks) {
        for(auto& z : x.second) {
           z.second->Render();
        }
    }
}

void World::Generate() {
    for(int i = 0; i < 8 ; i++) {
        for(int j = 0; j < 8 ; j++) {
            CreateChunk(i, j);
        }
    }
}

float World::GenerateHeight(int x, int z) {
    float scale = 0.0625f;
    return glm::perlin(glm::vec2(x * scale, z * scale)) * 20.0f + 140.0f;
}

World::~World() {
    for(auto& x : chunks) {
        for(auto& z : x.second) {
            delete z.second;
        }
    }
}