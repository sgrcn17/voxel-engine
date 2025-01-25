#include "engine.hpp"

Window* Engine::window = nullptr;
Input* Engine::input = nullptr;
Renderer* Engine::renderer = nullptr;
Interface* Engine::interface = nullptr;
Camera* Engine::camera = nullptr;
DataCollection<Texture>* Engine::textureAtlas = nullptr;
DataCollection<Model>* Engine::blockModels = nullptr;
World* Engine::world = nullptr;

double Engine::lastFrame = 0.0d, Engine::deltaTime = 0.0d;

void Engine::Initialize() {
    glfwInit();

    textureAtlas = new DataCollection<Texture>("./../src/data/textures.json");
    blockModels = new DataCollection<Model>("./../src/data/models.json");
    textureAtlas->LoadData();
    blockModels->LoadData();

    window = new Window(SETTINGS::SCR_WIDTH, SETTINGS::SCR_HEIGHT, "Voxel-Engine");
    input = new Input(window->GetWindow());
    interface = new Interface(window->GetWindow());
    camera = new Camera();

    glEnable(GL_DEPTH_TEST);

    renderer = new Renderer();
    world = new World();
    world->Generate();
}

void Engine::Update() {
    input->ProcessInput(window->GetWindow());

    camera->Move(window->GetWindow(), deltaTime);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(world) world->Update();

    renderer->Render();
    if(world) world->Render();
    
    interface->NewFrame();
    interface->RenderSettingsWindow();
    interface->RenderTextureList(renderer->GetTexture(), textureAtlas);
    interface->RenderModelList(renderer->GetTexture(), textureAtlas, blockModels);
    interface->Render();

    deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();

    glfwSwapBuffers(window->GetWindow());
    glfwPollEvents();
}

void Engine::Terminate() {
    textureAtlas->SaveData();
    blockModels->SaveData();

    delete window;
    delete input;
    delete renderer;
    delete interface;
    delete camera;
    delete textureAtlas;
    delete blockModels;
    delete world;

    glfwTerminate();
}

void Engine::Run()
{
    try {
        Initialize();
        while(!glfwWindowShouldClose(window->GetWindow())) {
            Update();
        }
        Terminate();
    } catch(const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}