#include "interface.hpp"

Interface::Interface(GLFWwindow* window) {
    Init(window);
}

Interface::~Interface() {
    Cleanup();
}

void Interface::Init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui::StyleColorsDark();
}

void Interface::RenderSettingsWindow() {
    ImGui::Begin("Settings", &showSettingsWindow);
    ImGui::SliderFloat("Sensitivity", &SETTINGS::SENSITIVITY, 1.0f, 360.0f);
    ImGui::SliderFloat("Camera Speed", &SETTINGS::CAMERA_SPEED, 1.0f, 100.0f);
    ImGui::End();
}

void Interface::RenderTextureList(unsigned int& tex, DataCollection<Texture>* textureAtlas) {
    ImGui::Begin("Texture List", &showTextureList);
    ImGui::BeginChild("Texture List", ImVec2(0, 144), true, ImGuiWindowFlags_AlwaysHorizontalScrollbar);

    for (int i = 0; i < textureAtlas->size(); ++i) {
        int x = (*textureAtlas)[i].xPos;
        int y = (*textureAtlas)[i].yPos;
        ImVec2 uv0(x * 0.03125f, y * 0.03125f);
        ImVec2 uv1((x + 1) * 0.03125f, (y + 1) * 0.03125f);

        ImGui::PushID(i);
        if (ImGui::Selectable("", selectedTextureIndex == i, 0, ImVec2(62, 64))) {
            selectedTextureIndex = i;
        }
        
        ImVec2 p = ImGui::GetItemRectMin();
        ImGui::GetWindowDrawList()->AddImage(
            (void*)(intptr_t)tex, 
            ImVec2(p.x + 2, p.y + 2), 
            ImVec2(p.x + 66, p.y + 66), 
            uv0, 
            uv1
        );

        ImGui::PopID();
        ImGui::SameLine();
    }

    ImGui::EndChild();

    if (selectedTextureIndex != -1) {
        Texture& selectedTexture = (*textureAtlas)[selectedTextureIndex];
        ImGui::Text("Selected Texture Parameters:");
        ImGui::Text("ID: %d", selectedTexture.GetID());

        char nameBuffer[128];
        strncpy(nameBuffer, selectedTexture.name.c_str(), sizeof(nameBuffer));
        nameBuffer[sizeof(nameBuffer) - 1] = '\0';

        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
            selectedTexture.name = std::string(nameBuffer);
        }
        
        ImGui::InputInt("X Position", &selectedTexture.xPos);
        ImGui::InputInt("Y Position", &selectedTexture.yPos);
    }

    ImGui::End();
}

void Interface::RenderModelList(unsigned int& tex, DataCollection<Texture>* textureAtlas, DataCollection<Model>* blockModels) {
    //TO DO
}

void Interface::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Interface::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Interface::Cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}