#pragma once

#include <string>
#include <vector>
#include "Point2D.h"

class Polygon
{
private:
	std::string Name;
	std::vector<Point2D> Vertices;

public:
	Polygon(const std::string& name, const std::vector<Point2D>& vertices);

	const std::string& GetName() const;
	const std::vector<Point2D>& GetVertices() const;
	std::vector<Point2D>& GetVertices();

	double CalculateArea() const;
	void TranslatePolygon(Polygon& polygon, const Point2D& offset);
};