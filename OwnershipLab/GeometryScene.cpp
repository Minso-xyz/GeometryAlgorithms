#include "GeometryScene.h"
#include <iostream>

void GeometryScene::AddGeometry(std::unique_ptr<Geometry> geometry)
{
	Geometries.push_back(std::move(geometry));
}

const std::vector<std::unique_ptr<Geometry>>& GeometryScene::GetGeometries() const
{
	return Geometries;
}

void GeometryScene::PrintGeometries() const
{
	for (const std::unique_ptr<Geometry>& geometry : Geometries)
	{
		std::cout << geometry->GetType() << std::endl;
	}
}
