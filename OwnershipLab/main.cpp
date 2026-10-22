#include <iostream>
#include "Point2D.h"
#include "Polygon.h"
#include <memory>

// the value will be copied and the calculated value will be discarded in the end of the fuction
void MovePoint_Value(Point2D point)
{
    point.X += 10;
    point.Y += 10;

    std::cout << "Inside fuction (Value): "
        << point.X << ", "
        << point.Y << std::endl;
}

void MovePoint_Reference(Point2D& point)
{
    point.X += 10;
    point.Y += 10;

    std::cout << "Inside fuction (Reference): "
        << point.X << ", "
        << point.Y << std::endl;
}

void MovePoint_Pointer(Point2D* point)
{
    if (point == nullptr)
    {
        std::cout << "No point!" << std::endl;
        return;
    }

    std::cout << "Inside fuction (Pointer): "
        << point->X << ", "
        << point->Y << std::endl;

    std::cout << "Pointer: "
        << point
        << std::endl;

    std::cout << "Actual point address: "
        << &(*point)
        << std::endl;

    point->X += 10;
    point->Y += 10;
}

double DistanceFromOrigin(const Point2D& point)  // not copy the original point, but read it
{
    //point.X = 100;  // it cannot be modified because it is being accessed through a "const" object

    return std::sqrt((point.X * point.X) + (point.Y * point.Y));
}




int main()
{
    // smart pointers
    Point2D pt{ 10,20 };

    Point2D* ptr = &pt;

    std::cout << pt.X << std::endl;
    std::cout << (*ptr).X << std::endl;
    std::cout << ptr->X << std::endl;

    std::cout << "" << std::endl;
    // Polygon
    std::vector<Point2D> vertices =
    {
        {0,0},
        {10,0},
        {10,5},
        {0,5}
    };

    std::unique_ptr<Polygon> polygonPtr = std::make_unique<Polygon>("Unique Polygon", vertices);


    Polygon polygon("Subject Polygon", vertices);

    std::cout << polygon.GetName() << std::endl;
    std::cout << polygon.CalculateArea() << std::endl;

    Point2D offset{ 5,10 };
    polygon.TranslatePolygon(offset);

    for (const Point2D& vertex : polygon.GetVertices())
    {
        std::cout << "(" << vertex.X << ", " << vertex.Y << ")" << std::endl;
    }


    std::cout << "" << std::endl;

    // Point
    Point2D point{ 5,10 };

    double distance = DistanceFromOrigin(point);
    std::cout << "Distance: "
        << distance << std::endl;


    std::cout << "Before: "
        << point.X << ", "
        << point.Y << std::endl;

    //MovePoint_Value(point);

    //MovePoint_Reference(point);

    MovePoint_Pointer(&point);
    std::cout << "Address in main: "
        << &point
        << std::endl;


    std::cout << "After: "
        << point.X << ", "
        << point.Y << std::endl;
}
