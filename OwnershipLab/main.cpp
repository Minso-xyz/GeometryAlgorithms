#include <iostream>
#include "Point2D.h"

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


int main()
{
    Point2D point{ 5,10 };

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
