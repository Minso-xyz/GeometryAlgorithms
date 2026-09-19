#pragma once

class HEVertex;
class HEFace;

class HEHalfEdge
{
public:

	HEVertex* Origin = nullptr;
	HEHalfEdge* Next = nullptr;
	HEHalfEdge* Twin = nullptr;
	HEFace* Face = nullptr;
};