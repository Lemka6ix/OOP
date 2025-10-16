#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>

struct point3d {
    double x, y, z;
    point3d(double x = 0.0, double y = 0.0, double z = 0.0);
    void print() const;
    double getBackX() const;
    double getBackY() const;
    double getBackZ() const;
};
#endif 