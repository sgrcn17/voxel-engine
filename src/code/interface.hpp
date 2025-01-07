#pragma once

#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "stb/stb_image.hpp"
#include "settings.hpp"
#include "dataCollection.hpp"
#include "texture.hpp"
#include "model.hpp"

class Interface {
public:
    Interface(GLFWwindow* window);
    ~Interface();

    void NewFrame();
    void Render();
    void RenderSettingsWindow();
    void RenderTextureList(unsigned int& tex, DataCollection<Texture>* textureAtlas);
    void RenderModelList(unsigned int& tex, DataCollection<Texture>* textureAtlas, DataCollection<Model>* blockModels);

private:

    int selectedTextureIndex = -1;
    bool showSettingsWindow = true;
    bool showTextureList = true;

    void Init(GLFWwindow* window);
    void Cleanup();
};