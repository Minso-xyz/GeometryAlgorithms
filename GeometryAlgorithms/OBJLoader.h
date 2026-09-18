#pragma once

#include <string>
#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <Point3D.h>
#include <Vertex.h>
#include <Face.h>

class OBJLoader
{
public:
	static Mesh Load(const std::string& filePath)
	{
		std::ifstream file(filePath);
		Mesh mesh;

		std::string line;

		while (std::getline(file, line))
		{
			if (line.rfind("v", 0) == 0)
			{
				int start = line.rfind("v");
				std::string vertices = line.substr(start + 1, line.size());

				std::stringstream ss(vertices);
				double x, y, z;
				ss >> x >> y >> z;

				Vertex vertex;
				vertex.Position = Point3D(x, y, z);
				mesh.Vertices.push_back(vertex);
			}

			if (line.rfind("f",0) == 0)
			{
				int start = line.find("f");
				std::string faces = line.substr(start + 1, line.size());

				std::stringstream ss(faces);
				int v0_index, v1_index, v2_index;
				ss >> v0_index >> v1_index >> v2_index;

				Face face;
				face.V0 = v0_index - 1;
				face.V1 = v1_index - 1;
				face.V2 = v2_index - 1;

				mesh.Faces.push_back(face);
			}
		}

		// Create the triangles from the extracted vertices and faces
		for (const Face& face : mesh.Faces)
		{
			Point3D a = mesh.Vertices[face.V0].Position;
			Point3D b = mesh.Vertices[face.V1].Position;
			Point3D c = mesh.Vertices[face.V2].Position;
			Triangle triangle(a, b, c);

			mesh.Triangles.push_back(triangle);
		}
		return mesh;
	}
};