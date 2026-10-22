#include "Polygon.h"
#include <cmath>

Polygon::Polygon(const std::string& name, const std::vector<Point2D>& vertices)
	: Name(name), Vertices(vertices)
{

}

const std::string& Polygon::GetName() const
{
	return Name;
}

const std::vector<Point2D>& Polygon::GetVertices() const
{
	return Vertices;
}

std::vector<Point2D>& Polygon::GetVertices()
{
	return Vertices;
}

double Polygon::CalculateArea() const
{
	if (Vertices.size() < 3)
	{
		return 0.0;
	}

	double area = 0.0;

	for (size_t i = 0; i < Vertices.size(); i++)
	{
		size_t next = (i + 1) % Vertices.size();

		area += Vertices[i].X * Vertices[next].Y;
		area -= Vertices[next].X * Vertices[i].Y;
	}
	return std::abs(area) * 0.5;
}

void Polygon::TranslatePolygon(const Point2D& offset)
{
	for (Point2D& vertex : Vertices)
	{
		vertex.X += offset.X;
		vertex.Y += offset.Y;
	}
}