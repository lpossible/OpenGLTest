#include"MyShader.h"

const int WIDTH = 800;
const int HEIGHT = 600;

//������ɫ��
const char* vertexShaderSource = "#version 330 core\n"
"layout(location=0) in vec3 aPos;\n"
"layout(location=1) in vec3 aColor;\n"
"out vec4 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position=vec4(aPos,1.0f);\n"
"ourColor=vec4(aColor,1.0f);\n"
"}\0";

//Ƭ����ɫ��
const char* fragmentShaderSource = "#version 330 core\n"
"in vec4 ourColor;\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor=ourColor;\n"
"}\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGl", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return -1;
	}
	//�������㻺�����
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//���������������
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//���������ݸ��Ƶ�������
	float vertices[] = {
		// λ��              // ��ɫ
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//���嶥������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//
	MyShader shader = MyShader(vertexShaderSource, fragmentShaderSource);
	//
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return -1;
}