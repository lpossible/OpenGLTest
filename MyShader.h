#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>

class MyShader
{
public:
	MyShader(const char* vertexShaderSource, const char* fragmentShaderSource);
	void use();
private:
	unsigned int shader;
};
