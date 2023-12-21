#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    
	std::string GetFileContents(const char* filename);

	void Activate();
	void Delete();

private:
	GLuint ID;
};
#endif