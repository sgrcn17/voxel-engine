#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Shader {
    unsigned int ID;

    Shader(const std::string vertexPath, const std::string fragmentPath) {
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        std::string vShaderStr = vShaderStream.str();
        std::string fShaderStr = fShaderStream.str();
        const char* vShaderCode = vShaderStr.c_str();
        const char* fShaderCode = fShaderStr.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    __attribute__((always_inline)) inline void use() const { glUseProgram(ID); }

    __attribute__((always_inline)) inline void setBool(std::string_view name, bool value) const { 
        glUniform1i(glGetUniformLocation(ID, name.data()), (int)value); 
    }
    __attribute__((always_inline)) inline void setInt(std::string_view name, int value) const { 
        glUniform1i(glGetUniformLocation(ID, name.data()), value); 
    }
    __attribute__((always_inline)) inline void setFloat(std::string_view name, float value) const { 
        glUniform1f(glGetUniformLocation(ID, name.data()), value); 
    }
    __attribute__((always_inline)) inline void setMat4(std::string_view name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, &mat[0][0]);
    }
};
