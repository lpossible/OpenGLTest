#include<glad/glad.h>
#include<GLFW/glfw3.h>
const int WIDTH = 800;
const int HEIGHT = 600;
void framsize_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwTerminate();
	}
}
int main()
{
	glfwInit();
	//����opengl�汾������Ⱦģʽ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//����opengl������
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpengl", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//���ô��ڱ仯�ص�����
	glfwSetFramebufferSizeCallback(window, framsize_callback);
	//����opengl������ַָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
	}
	while (!glfwWindowShouldClose(window))
	{
		//����ˢ��ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//ʹ����ɫ����ˢ��
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;	
}