#include <GLFW/glfw3.h>
#include "Imgui.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "Polygon.h"

Camera* gCamera = nullptr;

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

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
	glEnable(GL_DEPTH_TEST);
	glfwSetScrollCallback(window, ScrollCallback);

	Mesh meshTriangle;
	meshTriangle.Triangles.push_back(
		Triangle(
			Point3D(-100, -100, 0),
			Point3D(100, -100, 0),
			Point3D(0, 100, 0)
		));

	Polygon square;
	square.Vertices =
	{
	{0,0},
	{10,0},
	{10,10},
	{0,10}
	};

	Renderer renderer;
	Camera camera;
	gCamera = &camera;

	camera.SetIsometricView();

	//LoadBunny(camera);  // Load the Bunny OBJ file and set the view

	// Fit the view as the size of the polygon
	camera.FitPolygonView(square);

	while (!glfwWindowShouldClose(window))
	{
		int width;
		int height;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.ApplyProjection(width, height);
		camera.ApplyView();
		renderer.DrawCoordinateAxis();

		camera.HandleMouse(window);

		//RenderBunny(renderer, objMesh);   // Render the bunny meshes

		renderer.DrawPolygon(square);

		glfwSwapBuffers(window);
		glfwPollEvents();   // handle the mouse/keyboard inputs
		camera.HandleInput(window);
	}

	glfwTerminate();

	return 0;
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (gCamera)
	{
		gCamera->HandleScroll(yOffset);  // only yOffset is used (Up-down mouse wheel)
	}
}

void LoadBunny(Camera camera)
{
	// Load the Stanford Bunny obj file
	OBJLoader objLoader;
	Mesh objMesh = objLoader.Load("..\\stanford-bunny.obj");

	// Fit the view as the size of the bunny
	BoundingBox boxBunny = objMesh.GetBoundingBox();
	camera.FitTargetBox(boxBunny);
}

void RenderBunny(Renderer renderer, Mesh objMesh)
{
	//renderer.DrawMesh(meshTriangle);
	renderer.DrawMesh(objMesh);   // Render the Stanford Bunny

	// Render the normal vector on each face
	for (auto triangle : objMesh.Triangles)
	{
		renderer.DrawNormal(triangle);
	}

	// Render the vertex normal vector on each vertex
	objMesh.CalculateVertexNormals();
	for (auto vertex : objMesh.Vertices)
	{
		renderer.DrawVertexNormal(vertex);
	}
}