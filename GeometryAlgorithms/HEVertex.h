#pragma once
#include "Point3D.h"

class HEHalfEdge;

class HEVertex
{
public:
	Point3D Position;
	HEHalfEdge* Edge = nullptr;
};