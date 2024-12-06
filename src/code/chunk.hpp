#pragma once

class Chunk {
    private:

    int blockIds[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];

    const unsigned int CHUNK_SIZE = 16, CHUNK_HEIGHT = 256;
};