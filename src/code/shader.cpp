#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    auto getShaderCode = [](const char* path) -> std::string {
        std::ifstream file;
        try {
            file.open(path);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            return stream.str();
        } catch (const std::ifstream::failure& e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
            return "";
        }
    };

    std::string vertexCode = getShaderCode(vertexPath);
    std::string fragmentCode = getShaderCode(fragmentPath);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    auto makeShader = [](GLuint& _id, const char* code, GLenum type) {
        _id = glCreateShader(type);
        glShaderSource(_id, 1, &code, NULL);
        glCompileShader(_id);
        GLint success;
        glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(_id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
    };

    GLuint vertex, fragment;
    makeShader(vertex, vShaderCode, GL_VERTEX_SHADER);
    makeShader(fragment, fShaderCode, GL_FRAGMENT_SHADER);

    Shader::id = glCreateProgram();
    glAttachShader(Shader::id, vertex);
    glAttachShader(Shader::id, fragment);
    glLinkProgram(Shader::id);
    GLint success;

    glGetProgramiv(Shader::id, GL_LINK_STATUS, &success);
    if(!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(Shader::id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(Shader::id);
}

void Shader::use() const {
    glUseProgram(Shader::id);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(Shader::id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(Shader::id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(Shader::id, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(Shader::id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}