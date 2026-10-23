#pragma once

#include "Geometry.h"
#include "Point2D.h"

class Line : public Geometry
{
private:
	Point2D Start;
	Point2D End;

// initialization constructor
public:
	Line(const Point2D& start, const Point2D& end)
		: Start(start), End(end)
	{

	}

	std::string GetType() const override
	{
		return "Line";
	}
};