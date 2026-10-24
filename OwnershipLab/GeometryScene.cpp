#include "GeometryScene.h"

void GeometryScene::AddGeometry(std::unique_ptr<Geometry> geometry)
{
	Geometries.push_back(std::move(geometry));
}

const std::vector<std::unique_ptr<Geometry>>& GeometryScene::GetGeometries() const
{
	return Geometries;
}
