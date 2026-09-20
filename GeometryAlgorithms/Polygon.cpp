#include "Polygon.h"

Point2D Polygon::GetMinPoint() const
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

Point2D Polygon::GetMaxPoint() const
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

// Shoelace formula
double Polygon::CalculateSignedArea() const
{
	double sum1 = 0;
	double sum2 = 0;
	
	int count = Vertices.size();

	for (int i = 0; i < count; i++)
	{
		int next = (i + 1) % count;

		sum1  = sum1 + Vertices[i].X * Vertices[next].Y;
		sum2 = sum2 + Vertices[i].Y * Vertices[next].X;
	}

	double signedArea = (sum1 - sum2) * 0.5;
	return signedArea;
}

double Polygon::CalculateArea() const
{
	double signedArea = CalculateSignedArea();
	return std::abs(signedArea);
}

bool Polygon::IsClockwise() const
{
	return CalculateSignedArea() > 0;
}

bool Polygon::IsCounterClockwise() const
{
	return !IsClockwise();
}

