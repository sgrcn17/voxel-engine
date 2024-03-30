#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_impl_glfw.h"
#include "../include/imgui/imgui_impl_opengl3.h"
#include "../render/shader.hpp"
#include "../render/vbo.hpp"
#include "../render/vao.hpp"
#include "../render/ebo.hpp"
#include "stb/stb_image.hpp"
#include "../render/texture.hpp"
#include "../core/camera.hpp"
#include "../core/chunk.hpp"
#include "../utils/DataLoader.hpp"

class Game {
public:
    void Run();

protected:
    void Init();
    void Update();
    void Render();
    void Shutdown();

    const unsigned int SCR_WIDTH = 1600;
    const unsigned int SCR_HEIGHT = 1600;

    GLFWwindow* window;
    Shader* shaderProgram;
    Texture* atlas;
    Camera* camera;

    Chunk* chunk;
};

#endif