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
	double Orientation(const Point2D& p) const
	{
		Vector2D ab = Start.VectorTo(End);
		Vector2D ap = Start.VectorTo(p);

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
		double o1 = Orientation(c);
		double o2 = Orientation(d);
		double o3 = other.Orientation(a);
		double o4 = other.Orientation(b);

		// if the orientation is the opposite, the segments intersect each other
		if (((o1 < 0) != (o2 < 0)) && ((o3 < 0) != (o4 < 0))) 
		{
			intersects = true;
		}

		const double epsilon = 1e-9;

		// if the end points meet
		if (std::abs(o1) < epsilon && IsPointOnSegment(c)) intersects = true;  // point c is on the segment ab
		if (std::abs(o2) < epsilon && IsPointOnSegment(d)) intersects = true;  // point d is on the segment ab
		if (std::abs(o3) < epsilon && IsPointOnSegment(a)) intersects = true;  // point a is on the segment cd
		if (std::abs(o4) < epsilon && IsPointOnSegment(b)) intersects = true;  // point b is on the segment cd

		return intersects;
	}

public:
	bool IsPointOnSegment(const Point2D& point) const
	{
		const double epsilon = 1e-9;

		double orientation = Orientation(point);

		if (std::abs(orientation) > epsilon)
		{
			return false;
		}

		// Check if point is on the segment
		bool withinX = point.X >= std::min(Start.X, End.X) - epsilon && point.X <= std::max(Start.X, End.X) + epsilon;
		bool withinY = point.Y >= std::min(Start.Y, End.Y) - epsilon && point.Y <= std::max(Start.Y, End.Y) + epsilon;

		return withinX && withinY;
	}

public:
	Point2D IntersectionPoint(const Segment2D& other)
	{
		// Points of the segments
		Point2D a = Start;
		Point2D b = End;
		Point2D c = other.Start;
		Point2D d = other.End;

		Vector2D ab = a.VectorTo(b);
		Vector2D cd = c.VectorTo(d);
		Vector2D ac = a.VectorTo(c);

		double denominator = ab.Cross(cd);

		if (std::abs(denominator) < 1e-9)  // tolerance
		{
			throw std::runtime_error("No intersection point exists.");   // Segment AB and CD are in parallel
		}
		
		double t = ac.Cross(cd) / ab.Cross(cd);

		// P = A + t (B - A)
		Point2D p = a + (ab * t);

		return p;
	}


	// Triangluation
	// Boolean
	// Offset
	// SVG Export
};
