#include "shaderClass.h"

/*string get_file_contents(const char* filename)
{
	ifstream in(filename, ios::binary);
	if (in)
	{
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}*/

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//string vertexCode = get_file_contents(vertexFile);
	//string fragmentCode = get_file_contents(fragmentFile);

	//const char* vertexSource = vertexCode.c_str();
	//const char* fragmentSource = fragmentCode.c_str();
}