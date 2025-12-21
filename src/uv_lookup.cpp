#include "uv_lookup.hpp"
#include <glad/glad.h>

#include "uv_lookup.hpp"
#include "blockData.hpp"
#include <glad/glad.h>

UVLookup::UVLookup() {
    auto encodeUV = [](float u, float v) -> float {
        unsigned int uInt = static_cast<unsigned int>(u * 65535.0f + 0.5f) & 0xFFFFu;
        unsigned int vInt = static_cast<unsigned int>(v * 65535.0f + 0.5f) & 0xFFFFu;
        unsigned int encoded = (uInt << 16) | vInt;
        return *reinterpret_cast<float*>(&encoded);
    };
    
    for(int texY = 0; texY < ATLAS_SIZE; ++texY) {
        for(int texX = 0; texX < ATLAS_SIZE; ++texX) {
            float uMin = static_cast<float>(texX) / ATLAS_SIZE;
            float uMax = static_cast<float>(texX + 1) / ATLAS_SIZE;
            int vFromBottom = ATLAS_SIZE - texY - 1;
            float vMin = static_cast<float>(vFromBottom) / ATLAS_SIZE;
            float vMax = static_cast<float>(vFromBottom + 1) / ATLAS_SIZE;
            
            size_t baseIndex = (texY * ATLAS_SIZE + texX) * 4;
            
            encoded[baseIndex + 0] = encodeUV(uMin, vMin); // bottom-left
            encoded[baseIndex + 1] = encodeUV(uMax, vMin); // bottom-right
            encoded[baseIndex + 2] = encodeUV(uMax, vMax); // top-right
            encoded[baseIndex + 3] = encodeUV(uMin, vMax); // top-left
        }
    }
}

UVLookup uvLookup;