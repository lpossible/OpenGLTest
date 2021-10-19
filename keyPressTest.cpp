#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"MyShader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


const int WIDTH = 800;
const int HEIGHT = 600;

//顶点着色器
const char* vertexShaderSource = "#version 330 core\n"
"layout(location=0) in vec3 aPos;\n"
"layout(location=1) in vec2 aTexCoord;\n"
"out vec2 TexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"gl_Position=projection*view*model*vec4(aPos,1.0f);\n"
"TexCoord=aTexCoord;\n"
"}\0";

//片段着色器
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"in vec3 ourColor;\n"
"uniform sampler2D texture1;\n"
"uniform sampler2D texture2;\n"
"void main(){\n"
" FragColor =mix(texture(texture1, TexCoord),texture(texture2, TexCoord),0.8f);\n"
"}\0";

//
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float currentFrame = glfwGetTime();

//检测键盘输入
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//向右向量
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
void processInput(GLFWwindow* window)
{
	float cameraSpeed = 5.0f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= cameraRight * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += cameraRight * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
//
bool firstMouse = true;
float lastX = 400.0f;
float lastY = 300.0f;
float pitch = 0.0f;
float yaw = -90.0f;
//鼠标切换方向向量
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

//视野缩放
float fov = 45.0f;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}
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
	//创建顶点缓冲对象
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//创建顶点数组对象
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//将顶点数据复制到缓冲中
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//
	unsigned int indices[] = {  // note that we start from 0!
	   0, 1, 2,  // first Triangle
	   0, 2, 3,  // second Triangle
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//定义顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//
	MyShader shader = MyShader(vertexShaderSource, fragmentShaderSource);
	//纹理设置
	shader.loadTexture("E:/OpenGLTest/Texture/awesomeface.png", GL_TEXTURE0, GL_RGBA, "texture1", 0);
	shader.loadTexture("E:/OpenGLTest/Texture/container.jpg", GL_TEXTURE1, GL_RGB, "texture2", 1);
	//定义模型矩阵，将局部坐标转换到世界坐标
	//沿x轴旋转时，角度为正向z轴正方向旋转
	//沿y轴旋转时，角度为正向x轴正方向旋转
	//沿z轴旋转时，角度为正向y轴正方向旋转
	glm::mat4 model;
	//model = glm::rotate(model, glm::radians(55.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//定义观察矩阵将世界坐标转换到观察坐标
	glm::mat4 view;
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//定义投影矩阵将观察坐标转换到裁剪坐标
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
	//位置信息
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	//
	//shader.setMat4("view", view);
	//shader.setMat4("projection", projection);
	//鼠标移动注册事件
	glfwSetCursorPosCallback(window, mouse_callback);
	//鼠标滚轮注册
	glfwSetScrollCallback(window, scroll_callback);
	//设置光标不可见
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//启动深度测试
	glEnable(GL_DEPTH_TEST);
	//
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		glBindVertexArray(vao);
		//
		view = glm::mat4(1.0f);
		//自动旋转
		/*float radius = 10.0f;
		float cameraX = radius * sin(glfwGetTime());
		float cameraZ = radius * cos(glfwGetTime());
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, cameraZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		shader.setMat4("view", view);*/
		//
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shader.setMat4("view", view);
		//
		projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(fov), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
		shader.setMat4("projection", projection);
		for (int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		shader.use();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return -1;
}