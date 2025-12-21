#pragma once

#include <string_view>
#include "blockData.hpp"

constexpr inline int SCR_WIDTH = 1600;
constexpr inline int SCR_HEIGHT = 900;
constexpr inline int CHUNK_SIZE = 16;
constexpr inline int CHUNK_HEIGHT = 256;
constexpr inline int WORLD_SIZE = 32; // in chunks
constexpr inline int CHUNKS_COUNT = WORLD_SIZE * WORLD_SIZE;
constexpr inline int BLOCKS_PER_CHUNK = CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT;

constexpr inline std::string_view projectPath = "C:\\Kodowanie i Pierdoly\\projects\\voxel-engine\\";
constexpr inline std::string_view shadersPath = projectPath;
constexpr inline std::string_view texturesPath = projectPath;
constexpr inline std::string_view texturemapPath = "C:\\Kodowanie i Pierdoly\\projects\\voxel-engine\\resources\\textures\\texturemap.png";
constexpr inline std::string_view fragmentShaderPath = "C:\\Kodowanie i Pierdoly\\projects\\voxel-engine\\resources\\shaders\\fragmentShader.glsl";
constexpr inline std::string_view vertexShaderPath = "C:\\Kodowanie i Pierdoly\\projects\\voxel-engine\\resources\\shaders\\vertexShader.glsl";

enum class ChunkNeighbour {
    North = 0,
    South,
    West,
    East,
    SIZE
};

enum class ChunkState {
    Free,
    UpdatedData,
    UpdatedMesh,
    SIZE
};