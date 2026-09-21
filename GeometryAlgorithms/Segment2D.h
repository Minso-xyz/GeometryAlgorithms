#pragma once
#include "Point2D.h"
#include "Vector2D.h"

class Segment2D
{
public:
	Point2D Start;
	Point2D End;

public:
	Segment2D();

	Segment2D(const Point2D& start, const Point2D& end)
	{
		Start = start;
		End = end;
	}

public:
	double Orientation(const Point2D& a, const Point2D& b, const Point2D& p)
	{
		Vector2D ab = a.VectorTo(b);
		Vector2D ap = a.VectorTo(p);

		double crossProduct = ab.Cross(ap);

		return crossProduct;
	}

public:
	bool Intersects(const Segment2D& other)
	{

	}

public:
	Point2D IntersectionPoint()
	{

	}

	// Triangluation
	// Boolean
	// Offset
	// SVG Export
};
