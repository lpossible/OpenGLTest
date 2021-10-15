#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"
class MyShader
{
public:
	MyShader(const char* vertexShaderSource, const char* fragmentShaderSource);
	void use();
	void setInt(const char* name,int value);
	void loadTexture(const char* filename, int textureId,int format, const char* textureName,int id);
	unsigned int shaderID;
};
