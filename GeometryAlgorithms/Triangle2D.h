#pragma once

#include "Point2D.h"

class Triangle2D {
public:
	Point2D A;
	Point2D B;
	Point2D C;

	Triangle2D(
		const Point2D& a,
		const Point2D& b,
		const Point2D& c
	);

public:
	double Area() const;
};