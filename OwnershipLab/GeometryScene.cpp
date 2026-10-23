#include "GeometryScene.h"

void GeometryScene::AddPolygon(std::unique_ptr<Polygon> polygon)
{
	//Polygons.push_back(std::move(polygon));
	Polygons.push_back(std::move(polygon));
}
