#include "Shader.h"


template<typename T>
void CreateShader(unsigned int &id, const char* shaderCode, T type) {
	id = glCreateShader(type);
	glShaderSource(id, 1, &shaderCode, NULL);
	glCompileShader(id);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode = GetFileContents(vertexPath);
	std::string fragmentCode = GetFileContents(fragmentPath);

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;

	CreateShader(vertex, vShaderCode, GL_VERTEX_SHADER);
	CreateShader(fragment, fShaderCode, GL_FRAGMENT_SHADER);
	
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

std::string Shader::GetFileContents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

void Shader::Use() { 
    glUseProgram(Shader::ID); 
}
    
void Shader::SetBool(const std::string &name, bool value) const {         
	glUniform1i(glGetUniformLocation(Shader::ID, name.c_str()), (int)value); 
}

void Shader::SetInt(const std::string &name, int value) const { 
	glUniform1i(glGetUniformLocation(Shader::ID, name.c_str()), value); 
}

void Shader::SetFloat(const std::string &name, float value) const { 
	glUniform1f(glGetUniformLocation(Shader::ID, name.c_str()), value); 
}