#include <GLFW/glfw3.h>
#include "Imgui.h"

int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window =glfwCreateWindow(1280,720,"Geometry Algorithms",nullptr,nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}