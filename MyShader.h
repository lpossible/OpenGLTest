#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
class MyShader
{
public:
	MyShader(const char* vertexShaderSource, const char* fragmentShaderSource);
	void use();
	void setInt(const char* name,int value);
	void setMat4(const char* name, glm::mat4 value);
	void loadTexture(const char* filename, int textureId,int format, const char* textureName,int id);
	unsigned int shaderID;
};
