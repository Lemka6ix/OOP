#include <point3d.hpp>
point3d::point3d(double x, double y, double z) : x(x), y(y), z(z) {}
void point3d::print() const {
    std::cout << "(" << x << ", " << y  << ", " << z << ")" << std::endl;
}
double point3d::getBackX() const { return x; }
double point3d::getBackY() const { return y; }
double point3d::getBackZ() const { return z; }
