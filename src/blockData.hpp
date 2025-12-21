#pragma once

#include <cstddef>
#include <array>

enum class FaceDirection {
    Front = 0,
    Back = 1,
    Left = 2,
    Right = 3,
    Top = 4,
    Bottom = 5,
    SIZE
};

enum class BlockType {
    Air = 0,
    AnySolid = 1,
    Grass = 2,
    Dirt = 3,
    Stone = 4,
    Sand = 5,
    SIZE
};

enum class TextureIndex {
    Stone = 0,
    Dirt = 1,
    Sand = 2,
    Grass = 3,
    GrassSide = 4,
    SIZE
};

constexpr inline int ATLAS_SIZE = 32;

struct TextureData {
    int x, y;
};

struct BlockData {
    TextureData textureData[static_cast<size_t>(TextureIndex::SIZE)];
    int blockTexture[static_cast<size_t>(BlockType::SIZE)][static_cast<size_t>(FaceDirection::SIZE)]; 

    BlockData() {
        textureData[static_cast<size_t>(TextureIndex::Stone)] = {0, 2};
        textureData[static_cast<size_t>(TextureIndex::Dirt)] = {0, 1};
        textureData[static_cast<size_t>(TextureIndex::Sand)] = {2, 1};
        textureData[static_cast<size_t>(TextureIndex::Grass)] = {0, 0};
        textureData[static_cast<size_t>(TextureIndex::GrassSide)] = {1, 0};

        blockTexture[static_cast<size_t>(BlockType::Air)][static_cast<size_t>(FaceDirection::Front)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Air)][static_cast<size_t>(FaceDirection::Back)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Air)][static_cast<size_t>(FaceDirection::Left)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Air)][static_cast<size_t>(FaceDirection::Right)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Air)][static_cast<size_t>(FaceDirection::Top)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Air)][static_cast<size_t>(FaceDirection::Bottom)] = static_cast<int>(TextureIndex::Stone);

        blockTexture[static_cast<size_t>(BlockType::AnySolid)][static_cast<size_t>(FaceDirection::Front)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::AnySolid)][static_cast<size_t>(FaceDirection::Back)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::AnySolid)][static_cast<size_t>(FaceDirection::Left)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::AnySolid)][static_cast<size_t>(FaceDirection::Right)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::AnySolid)][static_cast<size_t>(FaceDirection::Top)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::AnySolid)][static_cast<size_t>(FaceDirection::Bottom)] = static_cast<int>(TextureIndex::Stone);

        blockTexture[static_cast<size_t>(BlockType::Grass)][static_cast<size_t>(FaceDirection::Front)] = static_cast<int>(TextureIndex::GrassSide);
        blockTexture[static_cast<size_t>(BlockType::Grass)][static_cast<size_t>(FaceDirection::Back)] = static_cast<int>(TextureIndex::GrassSide);
        blockTexture[static_cast<size_t>(BlockType::Grass)][static_cast<size_t>(FaceDirection::Left)] = static_cast<int>(TextureIndex::GrassSide);
        blockTexture[static_cast<size_t>(BlockType::Grass)][static_cast<size_t>(FaceDirection::Right)] = static_cast<int>(TextureIndex::GrassSide);
        blockTexture[static_cast<size_t>(BlockType::Grass)][static_cast<size_t>(FaceDirection::Top)] = static_cast<int>(TextureIndex::Grass);
        blockTexture[static_cast<size_t>(BlockType::Grass)][static_cast<size_t>(FaceDirection::Bottom)] = static_cast<int>(TextureIndex::Dirt);

        blockTexture[static_cast<size_t>(BlockType::Dirt)][static_cast<size_t>(FaceDirection::Front)] = static_cast<int>(TextureIndex::Dirt);
        blockTexture[static_cast<size_t>(BlockType::Dirt)][static_cast<size_t>(FaceDirection::Back)] = static_cast<int>(TextureIndex::Dirt);
        blockTexture[static_cast<size_t>(BlockType::Dirt)][static_cast<size_t>(FaceDirection::Left)] = static_cast<int>(TextureIndex::Dirt);
        blockTexture[static_cast<size_t>(BlockType::Dirt)][static_cast<size_t>(FaceDirection::Right)] = static_cast<int>(TextureIndex::Dirt);
        blockTexture[static_cast<size_t>(BlockType::Dirt)][static_cast<size_t>(FaceDirection::Top)] = static_cast<int>(TextureIndex::Dirt);
        blockTexture[static_cast<size_t>(BlockType::Dirt)][static_cast<size_t>(FaceDirection::Bottom)] = static_cast<int>(TextureIndex::Dirt);

        blockTexture[static_cast<size_t>(BlockType::Stone)][static_cast<size_t>(FaceDirection::Front)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Stone)][static_cast<size_t>(FaceDirection::Back)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Stone)][static_cast<size_t>(FaceDirection::Left)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Stone)][static_cast<size_t>(FaceDirection::Right)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Stone)][static_cast<size_t>(FaceDirection::Top)] = static_cast<int>(TextureIndex::Stone);
        blockTexture[static_cast<size_t>(BlockType::Stone)][static_cast<size_t>(FaceDirection::Bottom)] = static_cast<int>(TextureIndex::Stone);

        blockTexture[static_cast<size_t>(BlockType::Sand)][static_cast<size_t>(FaceDirection::Front)] = static_cast<int>(TextureIndex::Sand);
        blockTexture[static_cast<size_t>(BlockType::Sand)][static_cast<size_t>(FaceDirection::Back)] = static_cast<int>(TextureIndex::Sand);
        blockTexture[static_cast<size_t>(BlockType::Sand)][static_cast<size_t>(FaceDirection::Left)] = static_cast<int>(TextureIndex::Sand);
        blockTexture[static_cast<size_t>(BlockType::Sand)][static_cast<size_t>(FaceDirection::Right)] = static_cast<int>(TextureIndex::Sand);
        blockTexture[static_cast<size_t>(BlockType::Sand)][static_cast<size_t>(FaceDirection::Top)] = static_cast<int>(TextureIndex::Sand);
        blockTexture[static_cast<size_t>(BlockType::Sand)][static_cast<size_t>(FaceDirection::Bottom)] = static_cast<int>(TextureIndex::Sand);
    }
};

extern BlockData blockData;

inline TextureData GetTextureData(TextureIndex textureIndex) {
    return blockData.textureData[static_cast<size_t>(textureIndex)];
}

inline TextureIndex GetBlockTexture(BlockType blockType, FaceDirection faceDirection) {
    return static_cast<TextureIndex>(blockData.blockTexture[static_cast<size_t>(blockType)][static_cast<size_t>(faceDirection)]);
}   
