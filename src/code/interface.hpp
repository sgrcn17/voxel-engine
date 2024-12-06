#pragma once

#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "stb/stb_image.hpp"
#include "settings.hpp"

class Interface {
public:
    Interface(GLFWwindow* window);
    ~Interface();

    void Render(unsigned int& tex);

private:
    void NewFrame();
    void RenderSettingsWindow();
    void RenderTextureList(unsigned int& tex);

    bool showSettingsWindow = true;
    bool showTextureList = true;

    void Init(GLFWwindow* window);
    void Cleanup();
};