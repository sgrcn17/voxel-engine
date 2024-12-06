#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "settings.hpp"

class Input {
public:
    Input(GLFWwindow* window);

    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void ProcessInput(GLFWwindow *window);

    static bool GetKeyPressed(int keyCode);
    static bool GetKeyHeld(int keyCode);
    static bool GetKeyReleased(int keyCode);

    static bool GetMouseButtonPressed(int mouseButton);
    static bool GetMouseButtonHeld(int mouseButton);
    static bool GetMouseButtonReleased(int mouseButton);

private:
    static float lastx, lasty;
    static bool pressed;
};