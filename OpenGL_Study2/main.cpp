#include "atlbase.h"
#include "atlstr.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define ABNORMAL_EXIT  \
{ \
	glfwTerminate(); \
	std::cout << "abnormal exit!!!" << std::endl; \
	return -1; \
}

void OutputDebugPrintf(const char* strOutputString, ...);

#define Log \
{ \
	OutputDebugPrintf("%s, %d\n", __FUNCTION__, __LINE__); \
}

void processInput(GLFWwindow *window);

int main()
{
	// init glfw and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow *window = glfwCreateWindow(800, 600, "Hello OpenGL", NULL, NULL);
	if (NULL == window) 
	{
		ABNORMAL_EXIT;
	}

	// make glfw context
	glfwMakeContextCurrent(window);

	// glad init all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		ABNORMAL_EXIT;
	}

	glViewport(0, 0, 800, 600);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		Log;
	}
}

void OutputDebugPrintf(const char* strOutputString, ...)
{
	char strBuffer[4096] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);
	//vsprintf(strBuffer,strOutputString,vlArgs);
	va_end(vlArgs);
	OutputDebugString(CA2W(strBuffer));
}