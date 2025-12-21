#pragma once

#include <array>
#include <cstddef>

#include "blockData.hpp"

struct UVLookup {
    std::array<float, ATLAS_SIZE * ATLAS_SIZE * 4> encoded;
    
    UVLookup();
};

extern UVLookup uvLookup;

inline float GetEncodedUV(int texX, int texY, int cornerIndex) {
    std::size_t index = (texY * ATLAS_SIZE + texX) * 4 + cornerIndex;
    return uvLookup.encoded[index];
}

