#ifndef VECTOR2D_H
#define VECTOR2D_H
// include all libraries in Vector2D.h becasue it is the top of all callable classes
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <list>
#include <iterator>
#include <vector>
using namespace std;

class Vector2D
{
    public:
        double x;
        double y;
        Vector2D();
        Vector2D(double in_x, double in_y);
};
Vector2D operator*(const Vector2D v_in, const double d);
Vector2D operator/(const Vector2D v_in, const double d);
ostream& operator<<(ostream& out, const Vector2D v_in);
#endif
