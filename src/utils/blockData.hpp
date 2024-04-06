#ifndef BLOCKDATA_HPP
#define BLOCKDATA_HPP

struct BlockData {
    float textureX, textureY;

    BlockData(float textureX, float textureY) : textureX(textureX), textureY(textureY) { }
};

#endif