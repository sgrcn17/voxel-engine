#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "settings.hpp"

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window() { glfwDestroyWindow(window); }
    GLFWwindow* GetWindow() const { return window; }

private:
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    GLFWwindow* window;
};