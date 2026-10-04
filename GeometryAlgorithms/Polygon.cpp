#include "Polygon.h"
#include "Segment2D.h"
#include <algorithm>

const double epsilon = 1e-9;

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

		sum1 = sum1 + Vertices[i].X * Vertices[next].Y;
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
		else if (!currentInside && nextInside)
		{
			Point2D intersectPoint = polygonEdge.IntersectionPoint(segment);
			clippedPolygon.Vertices.push_back(intersectPoint);
			clippedPolygon.Vertices.push_back(nextPoint);
		}

		// Outside to Outside
		else if (!currentInside && !nextInside)
		{
			// add nothing
		}
	}
	return clippedPolygon;
}

Polygon Polygon::Clip(const Polygon& clipPolygon) const
{
	Polygon result = *this;

	int count = clipPolygon.Vertices.size();

	for (int i = 0; i < count; i++)
	{
		int next = (i + 1) % count;

		Point2D start = clipPolygon.Vertices[i];
		Point2D end = clipPolygon.Vertices[next];

		Segment2D clipEdge(start, end);

		result = result.ClipAgainstEdge(clipEdge);
	}
	return result;
}

std::vector<Polygon::PolygonIntersection> Polygon::FindIntersections(const Polygon& other) const
{
	std::vector<PolygonIntersection> intersections;

	int countA = Vertices.size();  // The number of Polygon A vertices
	int countB = other.Vertices.size();   // The number of Polygon B vertices

	for (int i = 0; i< countA; i++) 
	{
		int nextA = (i + 1) % countA;
		Segment2D edgeA(Vertices[i], Vertices[nextA]);

		for (int j = 0; j < countB; j++)
		{
			int nextB = (j + 1) % countB;
			Segment2D edgeB(other.Vertices[j], other.Vertices[nextB]);

			if (edgeA.Intersects(edgeB))
			{
				Point2D intersectionPoint = edgeA.IntersectionPoint(edgeB);

				PolygonIntersection polygonIntersection;
				polygonIntersection.Point = intersectionPoint;
				polygonIntersection.EdgeIndexA = i;
				polygonIntersection.EdgeIndexB = j;

				// Calculate tA, tB
				Vector2D ab = Vertices[i].VectorTo(Vertices[nextA]);
				Vector2D cd = other.Vertices[j].VectorTo(other.Vertices[nextB]);
				Vector2D ac = Vertices[i].VectorTo(other.Vertices[j]);

				double denominator = ab.Cross(cd);

				if (std::abs(denominator) < epsilon)
				{
					// 2 segments are in parallel / collinear
					continue;
				}

				double tA = ac.Cross(cd) / denominator;
				double tB = ac.Cross(ab) / denominator;

				polygonIntersection.tA = tA;
				polygonIntersection.tB = tB;
					
				intersections.push_back(polygonIntersection);
			}
		}
	}
	return intersections;
}

std::vector<Point2D> Polygon::FindOutsideVertices(const Polygon& other) const
{
	std::vector<Point2D> outsideVertices;

	for (const Point2D& vertex : Vertices)
	{
		if (!other.ContainsPoint(vertex))
		{
			outsideVertices.push_back(vertex);
		}
	}
	return outsideVertices;
}

std::vector<Point2D> Polygon::BuildBoundaryWithIntersections(const std::vector<PolygonIntersection>& intersections, PolygonSide side) const
{
	std::vector<Point2D> boundary;

	for (int i = 0; i < Vertices.size(); i++)
	{
		// add the current polygon vertex
		boundary.push_back(Vertices[i]);

		// find the intersections in the edge [i]
		std::vector<PolygonIntersection> intersectionsInEdge;

		for (const PolygonIntersection& intersection : intersections)
		{
			int edgeIndex;

			if (side == PolygonSide::A)
			{
				edgeIndex = intersection.EdgeIndexA;
			}
			else   // PolygonSide::B
			{
				edgeIndex = intersection.EdgeIndexB;
			}

			if (edgeIndex == i)
			{
				intersectionsInEdge.push_back(intersection);
			}
		}

		// arrange the intersection points in the order of t [0-1]
		std::sort(intersectionsInEdge.begin(), intersectionsInEdge.end(),
			[side](const PolygonIntersection & a, const PolygonIntersection & b)
			{
				if (side == PolygonSide::A)
				{
					return a.tA < b.tA;
				}
				else   // PolygonSide::B
				{
					return a.tB < b.tB;
				}
			});

		// add the intersection points to boundary in order
		for (const PolygonIntersection& intersection : intersectionsInEdge)
		{
			boundary.push_back(intersection.Point);
		}
	}

	return boundary;
}

std::vector<Segment2D> Polygon::FindOutsideBoundarySegments(const std::vector<Point2D>& boundary, const Polygon& other) const
{
	std::vector<Segment2D> outsideSegments;

	int count = boundary.size();

	for (int i = 0; i < count; i++)
	{
		int next = (i + 1) % count;

		Point2D start = boundary[i];
		Point2D end = boundary[next];

		Point2D midPoint((start.X + end.X) / 2.0, (start.Y + end.Y) / 2.0);

		bool insideOther = other.ContainsPoint(midPoint);   

		// if midPoint (on the Edge of Polygon A) is outside from the other polygon (Polygon B)
		if (!insideOther)
		{
			outsideSegments.push_back(Segment2D(start, end));
		}
	}
	return outsideSegments;
}

Polygon Polygon::BuildPolygonFromSegments(const std::vector<Segment2D> segments) const
{
	
}