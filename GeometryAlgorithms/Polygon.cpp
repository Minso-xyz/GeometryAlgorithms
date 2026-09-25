#include "Polygon.h"
#include "Segment2D.h"

Point2D Polygon::GetMinPoint() const
{
	double minX = Vertices[0].X;
	double minY = Vertices[0].Y;

	for (auto vertex : Vertices)
	{
		if (minX >= vertex.X) minX = vertex.X;
		if (minY >= vertex.Y) minY = vertex.Y;
	}
	return Point2D(minX, minY);
}

Point2D Polygon::GetMaxPoint() const
{
	double maxX = Vertices[0].X;
	double maxY = Vertices[0].Y;

	for (auto vertex : Vertices)
	{
		if (maxX <= vertex.X) maxX = vertex.X;
		if (maxY <= vertex.Y) maxY = vertex.Y;
	}
	return Point2D(maxX, maxY);
}

// Shoelace formula
double Polygon::CalculateSignedArea() const
{
	double sum1 = 0;
	double sum2 = 0;
	
	int count = Vertices.size();

	for (int i = 0; i < count; i++)
	{
		int next = (i + 1) % count;

		sum1  = sum1 + Vertices[i].X * Vertices[next].Y;
		sum2 = sum2 + Vertices[i].Y * Vertices[next].X;
	}

	double signedArea = (sum1 - sum2) * 0.5;
	return signedArea;
}

double Polygon::CalculateArea() const
{
	double signedArea = CalculateSignedArea();
	return std::abs(signedArea);
}

bool Polygon::IsClockwise() const
{
	return CalculateSignedArea() > 0;
}

bool Polygon::IsCounterClockwise() const
{
	return !IsClockwise();
}

// Ray Casting
bool Polygon::ContainsPoint(const Point2D& point) const
{
	bool result = false;
	int intersectionCount = 0;
	int count = Vertices.size();

	for (int i = 0; i < count; i++)
	{
		int next = (i + 1) % count;

		Point2D a = Vertices[i];
		Point2D b = Vertices[next];

		// Check if there is an interection with the edge ab
		if ((a.Y > point.Y) != (b.Y > point.Y))  // one point is in the upper-side, the other point is in the lower-point (false != true : true, true!=true : false)
		{
			// calculate intersectionX
			double t = (point.Y - a.Y) / (b.Y - a.Y);  // ratio of the moving distance
			double intersectionX = a.X + (t * (b.X - a.X));  // x = x0 + dx (Linear Interpolation)

			// check if intersectionX cross the edge ab
			if (intersectionX > point.X) intersectionCount++;   // Ray goes to the right direction
		}
	}
	if (intersectionCount % 2 == 1)
	{
		result = true;
	}
	return result;
}

// Sutherland-Hodgman algorithm (Clipping polygons)
Polygon Polygon::ClipAgainstEdge(const Segment2D& segment) const
{
	Polygon clippedPolygon;

	int count = Vertices.size();

	for (int i = 0; i < count; i++)
	{
		int next = (1 + i) % count;

		Point2D current = Vertices[i];
		Point2D nextPoint = Vertices[next];
		Segment2D polygonEdge = Segment2D(current, nextPoint);
		
		double currentOrientation = segment.Orientation(current);
		double nextOrientation = segment.Orientation(nextPoint);

		// assuming the clip polygon vertices are CCW,
		// the left side of each clipping edge is inside
		bool currentInside = currentOrientation >= 0;
		bool nextInside = nextOrientation >= 0;

		// Inside to Inside
		if (currentInside && nextInside)
		{
			//clippedPolygon.Vertices.push_back(current);
			clippedPolygon.Vertices.push_back(nextPoint);
		}

		// Inside to Outside
		else if (currentInside && !nextInside)
		{
			Point2D intersectPoint = polygonEdge.IntersectionPoint(segment);
			//clippedPolygon.Vertices.push_back(current);
			clippedPolygon.Vertices.push_back(intersectPoint);
		}

		// Outside to Inside
		if (!currentInside && nextInside)
		{
			Point2D intersectPoint = polygonEdge.IntersectionPoint(segment);
			clippedPolygon.Vertices.push_back(nextPoint);
			clippedPolygon.Vertices.push_back(intersectPoint);
		}

		// Outside to Outside
		if (!currentInside && !nextInside)
		{
			// add nothing
		}
	}
	return clippedPolygon;
}

