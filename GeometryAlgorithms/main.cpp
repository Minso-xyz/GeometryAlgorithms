#include <GLFW/glfw3.h>
#include "Imgui.h"
#include "Mesh.h"
#include "Renderer.h"

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

	Mesh mesh;
	mesh.triangles.push_back(
		Triangle(
			Point3D(-1, -1, 0),
			Point3D(1, -1, 0),
			Point3D(0, 1, 0)
		));

	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.DrawMesh(mesh);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}