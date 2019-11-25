#include "Point2D.h"
// default constructor
Point2D::Point2D()
{
    this -> x = 0.0;
    this -> y = 0.0;
}

Point2D::Point2D(double in_x, double in_y)
{
    this -> x = in_x;
    this -> y = in_y;
}

// return cartesian distance between two points
double GetDistanceBetween(Point2D p1, Point2D p2)
{
    double xDiff = pow(p2.x - p1.x, 2); // (x2-x1)^2
    double yDiff = pow(p2.y - p1.y, 2);

    return sqrt(xDiff + yDiff);
}

// overloaded output stream operator
ostream& operator<<(ostream& out, Point2D p_in)
{
    out << "(" << p_in.x << ", " << p_in.y << ")";
    return out;
}

// addition operator overload to add displacement vector
Point2D operator+(const Point2D p_in, const Vector2D v_in)
{
    Point2D endPoint(p_in.x + v_in.x, p_in.y + v_in.y);
    return endPoint;
}

// subtraction operator overload
Vector2D operator-(const Point2D p1, const Point2D p2)
{
    Vector2D endVec(p1.x - p2.x, p1.y - p2.y);
    return endVec;
}