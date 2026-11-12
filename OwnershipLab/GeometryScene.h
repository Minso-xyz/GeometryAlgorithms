#pragma once

#include <memory>
#include <vector>
#include "Polygon.h"

class GeometryScene
{
private:
	std::vector<std::unique_ptr<Geometry>> Geometries;

public:
	void AddGeometry(std::unique_ptr<Geometry> geometry);
	const std::vector<std::unique_ptr<Geometry>>& GetGeometries() const;
	void PrintGeometries() const;
};