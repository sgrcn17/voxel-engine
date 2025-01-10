#include "renderer.hpp"
#include "engine.hpp"

Renderer::Renderer() {
    shader = new Shader("./../src/shaders/vertexShader.glsl", "./../src/shaders/fragmentShader.glsl");

    glGenTextures(1, &texture); 
    glBindTexture(GL_TEXTURE_2D, texture);  

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("./../src/textures/atlas.png", &width, &height, &nrChannels, 0);

    if(data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

void Renderer::Render() {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SETTINGS::SCR_WIDTH / (float)SETTINGS::SCR_HEIGHT, 0.1f, 400.0f);

    shader->use();
    shader->setMat4("view", Engine::GetCamera()->GetViewMatrix());
    shader->setMat4("projection", projection);

    glBindTexture(GL_TEXTURE_2D, texture);
}