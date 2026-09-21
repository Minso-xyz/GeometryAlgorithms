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
		bool intersects = false;

		// Points of the segments
		Point2D a = Start;
		Point2D b = End;
		Point2D c = other.Start;
		Point2D d = other.End;

		// orientations of the segments
		double o1 = Orientation(a, b, c);
		double o2 = Orientation(a, b, d);
		double o3 = Orientation(c, d, a);
		double o4 = Orientation(c, d, b);

		// if the orientation is the opposite, the segments intersect each other
		if (((o1 < 0) != (o2 < 0)) && ((o3 < 0) != (o4 < 0))) 
		{
			intersects = true;
		}
		return intersects;
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
