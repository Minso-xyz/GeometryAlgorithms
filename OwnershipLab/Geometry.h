#pragma once
#include <string>

class Geometry
{
public:
	virtual std::string GetType() const = 0;
	virtual ~Geometry() = default;
};