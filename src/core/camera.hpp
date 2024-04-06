#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../render/shader.hpp"

class Camera {
public:
    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstClick = true;

    int screenWidth;
    int screenHeight;

    float speed = 0.006f;
    float sensitivity = 70.0f;

    Camera(int scrWidth, int scrHeight, glm::vec3 position);

    void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
    void Input(GLFWwindow* window);
};

#endif