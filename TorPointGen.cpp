#include "TorPointGen.h"
#include <iostream>
#include <cmath>

TorPointGenerator::TorPointGenerator(double R, double r) : R_(R), r_(r) {
    std::random_device rd;
    gen_.seed(rd());
}

point3d TorPointGenerator::rnd() {
    std::uniform_real_distribution<> rho_dist(R_ - r_, R_ + r_);
    std::uniform_real_distribution<> phi_dist(0, 2 * M_PI);
    std::uniform_real_distribution<> z_dist(0, r_);

    double rho, phi, z;
    do {
        rho = rho_dist(gen_);
        phi = phi_dist(gen_);
        z = z_dist(gen_);
    } while (std::pow(rho - R_, 2) + std::pow(z, 2) > r_ * r_);

    double x = rho * std::cos(phi);
    double y = rho * std::sin(phi);
    return point3d(x, y, z);
}

double TorPointGenerator::getR()
const { return R_; }
double TorPointGenerator::getr()
const { return r_; }

void TorPointGenerator::saveSettings(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "R: " << R_ << "\nr: " << r_ << std::endl;
        file.close();
    }
}