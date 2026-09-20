#pragma once
#include "Point3D.h"
#include "Line3D.h"
#include "Vertex.h"
#include "Edge.h"
#include "Circle3D.h"
#include "BSplineCurve.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Point2D.h"
#include "Polygon.h"

class Renderer
{
public:

	void DrawCoordinateAxis();
	void DrawPoint(const Point3D& point);
	void DrawLine(const Line3D& line);
	void DrawLine2(const Line3D& line);
	void DrawLine2D(const Point2D& pt1, const Point2D& pt2);
	void DrawCircle(const Circle3D& circle);
	void DrawPolyline(const std::vector<Point3D>& points);
	void DrawPolygon(const Polygon& polygon);
	void DrawBSplineCurve(const BSplineCurve& curve);
	void DrawVertex(const Vertex& vertex);
	void DrawEdge(const Edge& edge);
	void DrawCube();
	void DrawMesh(const Mesh& mesh);
	void DrawTriangle(const Triangle& triangle);
	void DrawBoundingBox(const BoundingBox& boundingBox);
	void DrawNormal(Triangle triangle);
	void DrawVertexNormal(const Vertex& vertex);
};