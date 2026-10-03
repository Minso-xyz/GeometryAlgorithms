#pragma once
#include <vector>
#include "Point2D.h"
#include "Segment2D.h"
#include "Polygon.h"

class Polygon
{
public:
	struct PolygonIntersection
	{
		Point2D Point;

		int EdgeIndexA;
		int EdgeIndexB;

		double tA;
		double tB;
	};

	enum class PolygonSide
	{
		A,B
	};

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
	std::vector<PolygonIntersection> FindIntersections(const Polygon& other) const;
	std::vector<Point2D> FindOutsideVertices(const Polygon& other) const;
	std::vector<Point2D> BuildBoundaryWithIntersections(const std::vector<PolygonIntersection>& intersections, PolygonSide side) const;
};