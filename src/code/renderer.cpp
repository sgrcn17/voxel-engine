#include "renderer.hpp"
#include "engine.hpp"

GLfloat vertices[] = {
    // positions          // colors           // texture coords
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.03125f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.03125f, 0.03125f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.03125f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.03125f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.03125f, 0.03125f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.03125f
    };
    
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 3, 7,
        7, 4, 0,
        1, 5, 6,
        6, 2, 1,
        0, 1, 5,
        5, 4, 0,
        3, 2, 6,
        6, 7, 3
    };

Renderer::Renderer() {
    vao = new VAO();
    vbo = new VBO();
    ebo = new EBO();

    vao->bind();
    vbo->bind();
    vbo->setData(sizeof(vertices), vertices, GL_STATIC_DRAW);
    ebo->bind();

    ebo->setData(sizeof(indices), indices, GL_STATIC_DRAW);
    vao->linkAttrib(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    vao->linkAttrib(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    vao->linkAttrib(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

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
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SETTINGS::SCR_WIDTH / (float)SETTINGS::SCR_HEIGHT, 0.1f, 100.0f);

    shader->use();
    shader->setMat4("view", Engine::GetCamera()->GetViewMatrix());
    shader->setMat4("projection", projection);

    glBindTexture(GL_TEXTURE_2D, texture);
    vao->bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    vao->unbind();
}