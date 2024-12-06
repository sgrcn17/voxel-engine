#include "engine.hpp"

Window* Engine::window = nullptr;
Input* Engine::input = nullptr;
Renderer* Engine::renderer = nullptr;
Interface* Engine::interface = nullptr;
Camera* Engine::camera = nullptr;
DataCollection<Texture>* Engine::textureAtlas = nullptr;

double Engine::lastFrame = 0.0d, Engine::deltaTime = 0.0d;

void Engine::Initialize() {
    glfwInit();
    window = new Window(SETTINGS::SCR_WIDTH, SETTINGS::SCR_HEIGHT, "Voxel-Engine");
    input = new Input(window->GetWindow());
    renderer = new Renderer();
    interface = new Interface(window->GetWindow());
    textureAtlas = new DataCollection<Texture>("./../src/data/textures.json");
    camera = new Camera();

    glEnable(GL_DEPTH_TEST);

    textureAtlas->LoadData();
}

void Engine::Update() {
    input->ProcessInput(window->GetWindow());

    camera->Move(window->GetWindow(), deltaTime);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->Render();
    interface->Render(renderer->GetTexture());

    deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();

    glfwSwapBuffers(window->GetWindow());
    glfwPollEvents();
}

void Engine::Terminate() {
    textureAtlas->SaveData();

    glfwTerminate();
}

void Engine::Run()
{
    Initialize();
    while(!glfwWindowShouldClose(window->GetWindow()))
    {
        Update();
    }
    Terminate();
}