#include "camera.hpp"

Camera::Camera()  {
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    UpdateVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::Rotate(float xoffset, float yoffset, float deltaTime) {
    yaw += xoffset * SETTINGS::SENSITIVITY * deltaTime;
    pitch += yoffset * SETTINGS::SENSITIVITY * deltaTime;

    if(pitch > 89.0f) pitch = 89.0f;
    if(pitch < -89.0f) pitch = -89.0f;
    
    UpdateVectors();
}

void Camera::Move(GLFWwindow* window, float deltaTime) {
    glm::vec3 direction = glm::vec3(0.0f);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        direction -= glm::normalize(glm::cross(right, glm::vec3(0.0f, 1.0f, 0.0f)));
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        direction += glm::normalize(glm::cross(right, glm::vec3(0.0f, 1.0f, 0.0f)));
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        direction -= glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        direction += glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        direction += glm::vec3(0.0f, 1.0f, 0.0f);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        direction -= glm::vec3(0.0f, 1.0f, 0.0f);
    }

    if(direction != glm::vec3(0.0f)) {
        position += glm::normalize(direction) * SETTINGS::CAMERA_SPEED * deltaTime;
    }
}

void Camera::UpdateVectors() {
    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}