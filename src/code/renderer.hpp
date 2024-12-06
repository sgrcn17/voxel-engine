#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "settings.hpp"
#include "vao.hpp"
#include "vbo.hpp"
#include "ebo.hpp"
#include "shader.hpp"
#include "stb/stb_image.hpp"

class Renderer {
public:
    Renderer();
    void Render();

    unsigned int& GetTexture() { return texture; }

private:
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
    Shader* shader;

    unsigned int texture;
};