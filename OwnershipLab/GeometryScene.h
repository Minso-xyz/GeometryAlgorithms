#pragma once

#include <memory>
#include <vector>
#include "Polygon.h"

class GeometryScene
{
private:
	std::vector<std::unique_ptr<Polygon>> Polygons;

public:
	void AddPolygon(std::unique_ptr<Polygon> polygon);
};