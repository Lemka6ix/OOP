#ifndef TORPOINTGEN_H
#define TORPOINTGEN_H

#include "point3d.h"
#include <random>

class TorPointGenerator {
    double R_;
    double r_;
    std::mt19937 gen_;

    public:
    TorPointGenerator(double R, double r);
    point3d rnd();
    double getR() const;
    double getr() const;
    void saveSettings(const std::string& filename = "setting.dat") const;
};

#endif