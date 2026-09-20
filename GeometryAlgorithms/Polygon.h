#pragma once
#include <vector>
#include "Point2D.h"

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
	
};