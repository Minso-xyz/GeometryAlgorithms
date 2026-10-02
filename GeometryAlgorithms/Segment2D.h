#pragma once
#include "Point2D.h"
#include "Vector2D.h"
#include <stdexcept>

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
	double Orientation(const Point2D& p) const;
	bool Intersects(const Segment2D& other) const;
	bool IsPointOnSegment(const Point2D& point) const;
	Point2D IntersectionPoint(const Segment2D& other);
};
