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

void Interface::RenderTextureList(unsigned int& tex) {
    ImGui::Begin("Texture List", &showTextureList);
    ImGui::BeginChild("Texture List", ImVec2(0, 300), true, ImGuiWindowFlags_HorizontalScrollbar);
    
    //0.03125f
    ImGui::Image((void*)(intptr_t)tex, ImVec2(1024, 1024), ImVec2(0, 0), ImVec2(1.0f, 1.0f));

    ImGui::EndChild();
    ImGui::End();
}

void Interface::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Interface::Render(unsigned int& tex) {
    Interface::NewFrame();

    Interface::RenderSettingsWindow();
    Interface::RenderTextureList(tex);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Interface::Cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}