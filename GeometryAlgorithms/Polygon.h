#pragma once
#include <vector>
#include "Point2D.h"
#include "Segment2D.h"
#include "Polygon.h"

class Polygon
{
public:
	std::vector<Point2D> Vertices;

public:
	Point2D GetMinPoint() const;
	Point2D GetMaxPoint() const;
	double CalculateSignedArea() const;
	double CalculateArea() const;
	bool IsClockwise() const;
	bool IsCounterClockwise() const;
	bool ContainsPoint(const Point2D& point) const;
	Polygon ClipAgainstEdge(const Segment2D& segment) const;
	Polygon Clip(const Polygon& clipPolygon) const;
	std::vector<Point2D> FindIntersections(const Polygon& other) const;
	
};