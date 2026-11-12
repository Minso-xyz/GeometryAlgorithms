#pragma once

#include "Geometry.h"
#include "Point2D.h"

class Circle : public Geometry
{
private:
	Point2D Center;
	double Radius;

public:
	Circle(const Point2D& center, const double& radius)
		: Center(center), Radius(radius)
	{

	}

	std::string GetType() const override
	{
		return "Circle";
	}
};