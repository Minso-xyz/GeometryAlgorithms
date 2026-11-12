#pragma once

#include <string>
#include <vector>
#include "Point2D.h"
#include "Geometry.h"

class Polygon : public Geometry
{
private:
	std::string Name;
	std::vector<Point2D> Vertices;

public:
	Polygon(const std::string& name, const std::vector<Point2D>& vertices);

	std::string GetType() const override
	{
		return "Polygon";
	}

	const std::string& GetName() const;
	const std::vector<Point2D>& GetVertices() const;
	std::vector<Point2D>& GetVertices();

	double CalculateArea() const;
	void TranslatePolygon(const Point2D& offset);
};