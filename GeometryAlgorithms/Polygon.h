#pragma once
#include <vector>
#include "Point2D.h"

class Polygon
{
public:
	std::vector<Point2D> Vertices;

public:
	Point2D GetMinPoint()
	{
		double minX = Vertices[0].X;
		double minY = Vertices[0].Y;

		for (auto vertex : Vertices)
		{
			if (minX >= vertex.X) minX = vertex.X;
			if (minY >= vertex.Y) minY = vertex.Y;
		}
		return Point2D(minX, minY);
	}

public:
	Point2D GetMaxPoint()
	{
		double maxX = Vertices[0].X;
		double maxY = Vertices[0].Y;

		for (auto vertex : Vertices)
		{
			if (maxX <= vertex.X) maxX = vertex.X;
			if (maxY <= vertex.Y) maxY = vertex.Y;
		}
		return Point2D(maxX, maxY);
	}
};