#include <iostream>
#include <vector>
#include <fstream>
#include "point3d.h"
#include "TorPointGen.h"
#ifdef WITH_MATHGL
#include <mg12/mgl.h>
#endif

int main() {
    double R, r;
    std::cout << "Введите параметры тора (R и r): ";
    std::cin >> R >> r;

    TorPointGenerator generation(R, r);
    generator.saveSettings();
}