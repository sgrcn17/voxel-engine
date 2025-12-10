#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utility>

#include "config.hpp"
#include "world.hpp"

struct Camera {
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw   = -90.0f;	
    float pitch =  0.0f;
    constexpr static float sensitivity = 0.1f; 
    constexpr static float cameraSpeed = 10.0f; 
    constexpr static float fov         = 45.0f;

    std::pair<int, int> currentChunk = std::make_pair(0, 0);

    void Rotate(float xoffset, float yoffset) {
        yaw += xoffset * sensitivity;
        pitch += yoffset * sensitivity;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }

    void Move(float horizontal, float vertical, float deltaTime) {
        cameraPos += horizontal * cameraSpeed * deltaTime * glm::normalize(glm::cross(cameraFront, cameraUp));
        cameraPos += vertical * cameraSpeed * deltaTime * cameraFront;
    }

    inline glm::mat4 View() {
        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }

    inline glm::mat4 Projection() {
        return glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    }

    inline glm::mat4 Model() {
        return glm::mat4(1.0f);
    }
};