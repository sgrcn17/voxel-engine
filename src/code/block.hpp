#pragma once

#include "settings.hpp"
#include <array>

class Block {
public:
    Block() = delete;
    Block(int id) { textureId.fill(0); }
    int GetId() const { return id; }
    int GetTextureId(SETTINGS::BLOCK_SIDE side) const { return textureId[side]; }
    void SetTextureId(SETTINGS::BLOCK_SIDE side, int id) { textureId[side] = id; }

private:
    int id, textureId[6];
};