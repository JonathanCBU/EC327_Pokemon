#include "Vector2D.h"
// default constructor
Vector2D::Vector2D()
{
    this -> x = 0.0;
    this -> y = 0.0;
}

Vector2D::Vector2D(double in_x, double in_y)
{
    this -> x = in_x;
    this -> y = in_y;
}

// overloaded multiplication operator
Vector2D operator*(const Vector2D v_in, const double d)
{
    Vector2D scaledVector(v_in.x * d, v_in.y * d);
    return scaledVector;
}

// overloaded division operator
Vector2D operator/(const Vector2D v_in, const double d)
{
    if (d != 0) {
        Vector2D scaledVector(v_in.x / d, v_in.y / d);
        return scaledVector;
    } else {
        return v_in;
    }
}

// overloaded output stream operator
ostream& operator<<(ostream& out, Vector2D v_in)
{
    out << "<" << v_in.x << ", " << v_in.y << ">";
    return out;
}
