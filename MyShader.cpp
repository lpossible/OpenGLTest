#include"MyShader.h"

MyShader::MyShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
void MyShader::use()
{
	glUseProgram(shaderID);
}

void MyShader::setInt(const char* name, int value)
{
	use();
	glUniform1i(glGetUniformLocation(shaderID, name), value);
}

void MyShader::setMat4(const char* name, glm::mat4 value)
{
	use();
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void MyShader::loadTexture(const char* filename,int textureId,int format,const char* textureName,int id)
{
	//��������
	stbi_set_flip_vertically_on_load(true);
	int width, height, nChannel;
	unsigned char* data = stbi_load(filename, &width, &height, &nChannel, 0);
	//����������
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(textureId);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//������ͼ���Ƶ����������
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	//���ɶ༶��Զ����
	glGenerateMipmap(GL_TEXTURE_2D);
	//
	stbi_image_free(data);
	setInt(textureName, id);
}
