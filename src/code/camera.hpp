#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "settings.hpp"

class Camera {
    public:
    Camera();
    void Rotate(float xoffset, float yoffset, float deltaTime);
    void Move(GLFWwindow* window , float deltaTime);
    glm::mat4 GetViewMatrix();
    glm::vec3 GetPosition() { return position; }

    private:
    void UpdateVectors();

    float yaw = -90.0f, pitch = 0.0f;
    glm::vec3 position, target, front, up, right;
};
