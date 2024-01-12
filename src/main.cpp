#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "shader.hpp"
#include "vbo.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "stb/stb_image.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "chunk.hpp"

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1600;
GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

unsigned int vao, ebo;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    Shader shaderProgram("../src/shaders/vertexShader.glsl", "../src/shaders/fragmentShader.glsl");

    Chunk chunk(0, 0, 0, shaderProgram);
    Chunk chunk1(16, 0, 0, shaderProgram);
    Chunk chunk2(32, 0, 0, shaderProgram);
    Chunk chunk3(48, 0, 0, shaderProgram);
    Chunk chunk4(64, 0, 0, shaderProgram);
    Chunk chunk5(80, 0, 0, shaderProgram);
    Chunk chunk6(96, 0, 0, shaderProgram);
    Chunk chunk7(112, 0, 0, shaderProgram);
    Chunk chunk8(128, 0, 0, shaderProgram);

    Texture dirt("../src/textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    dirt.texUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        camera.Input(window);
        camera.Matrix(45.0f, 0.1f, 400.0f, shaderProgram, "camMatrix");

        dirt.Bind();

        chunk.Draw();
        chunk1.Draw();
        chunk2.Draw();
        chunk3.Draw();
        chunk4.Draw();
        chunk5.Draw();
        chunk6.Draw();
        chunk7.Draw();
        chunk8.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
        
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    dirt.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}