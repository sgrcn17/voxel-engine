#include "input.hpp"
#include "engine.hpp"

float Input::lastx = -1.0f, Input::lasty = -1.0f;
bool Input::pressed = false;

Input::Input(GLFWwindow* window) {
    glfwSetCursorPosCallback(window, MouseCallback);
}

void Input::ProcessInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) pressed = true;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) pressed = false;

    if(pressed) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if(lastx == -1.0f) {
        lastx = xpos;
        lasty = ypos;
    }
    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos;
    lastx = xpos;
    lasty = ypos;

    if(pressed) Engine::GetCamera()->Rotate(xoffset, yoffset, Engine::GetDeltaTime());
}

bool Input::GetKeyPressed(int keyCode) {
    return glfwGetKey(Engine::GetWindow(), keyCode) == GLFW_PRESS;
}

bool Input::GetKeyHeld(int keyCode) {
    return false;
    //return glfwGetKey(Engine::GetWindow(), keyCode) == GLFW_REPEAT;
}

bool Input::GetKeyReleased(int keyCode) {
    return glfwGetKey(Engine::GetWindow(), keyCode) == GLFW_RELEASE;
}

bool Input::GetMouseButtonPressed(int mouseButton) {
    return glfwGetMouseButton(Engine::GetWindow(), mouseButton) == GLFW_PRESS;
}

bool Input::GetMouseButtonHeld(int mouseButton) {
    return false;
    //return glfwGetMouseButton(Engine::GetWindow(), mouseButton) == GLFW_REPEAT;
}

bool Input::GetMouseButtonReleased(int mouseButton) {
    return glfwGetMouseButton(Engine::GetWindow(), mouseButton) == GLFW_RELEASE;
}