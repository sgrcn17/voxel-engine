#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb/stb_image.hpp"
#include <string>
#include "texture.hpp"
#include "dataCollection.hpp"

class TextureAtlas : DataCollection<Texture> {
    public:
    void LoadTexture(int texWidth, int texHeight, string path);
    Texture& operator[](int index) { return textures[index]; }

    private:
    int width, height, nrChannels;
};