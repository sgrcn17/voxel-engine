#pragma once

#define DEBUG

constexpr inline int SCR_WIDTH = 1600;
constexpr inline int SCR_HEIGHT = 900;
constexpr inline int CHUNK_SIZE = 16;
constexpr inline int CHUNK_HEIGHT = 256;
constexpr inline int WORLD_SIZE = 128; // in chunks
constexpr inline int CHUNKS_COUNT = WORLD_SIZE * WORLD_SIZE;
constexpr inline int BLOCKS_PER_CHUNK = CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT;
constexpr inline int VERTICES_PER_CHUNK = 65536; // magic number 