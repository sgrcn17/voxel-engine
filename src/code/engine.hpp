#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

#include "vao.hpp"
#include "vbo.hpp"
#include "ebo.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "stb/stb_image.hpp"
#include "settings.hpp"
#include "interface.hpp"
#include "dataCollection.hpp"
#include "texture.hpp"
#include "window.hpp"
#include "input.hpp"
#include "renderer.hpp"

class Engine {

public:
    static void Run();

    static void Initialize();
    static void Update();
    static void Terminate();

    static double GetDeltaTime() { return deltaTime; }

    static Camera* GetCamera() { return camera; }
    static GLFWwindow* GetWindow() { return window->GetWindow(); }
    static DataCollection<Texture>* GetTextureAtlas() { return textureAtlas; }

private:
    static double lastFrame, deltaTime;

    static Window* window;
    static Input* input;
    static Renderer* renderer;
    static Interface* interface;
    static Camera* camera;
    static DataCollection<Texture>* textureAtlas;
};