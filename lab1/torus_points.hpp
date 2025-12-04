#ifndef TORUS_POINTS_HPP
#define TORUS_POINTS_HPP

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <cmath>
#include <stdexcept>

struct point3d {
    double x, y, z;

    point3d(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }
    
    double getBackX() const { return x; }
 
    double getBackY() const { return y; }
  
    double getBackZ() const { return z; }
};


class TorusPointGenerator {
private:
    double R;  ///< Большой радиус тора (расстояние от центра тора до центра трубки)
    double r;  ///< Малый радиус тора (радиус трубки)
    std::mt19937 generator;  ///< Генератор случайных чисел
    
public:
    TorusPointGenerator(double R = 5.0, double r = 2.0) : R(R), r(r) {
        std::random_device rd;
        generator.seed(rd());
    }

    point3d rnd() {
        // Используем параметрические уравнения тора
        // u, v - угловые параметры
        std::uniform_real_distribution<double> distU(0.0, 2.0 * M_PI);
        std::uniform_real_distribution<double> distV(0.0, M_PI);  // Только верхняя половина
        
        double u = distU(generator);
        double v = distV(generator);
        
        // Параметрические уравнения тора
        double x = (R + r * cos(v)) * cos(u);
        double y = (R + r * cos(v)) * sin(u);
        double z = r * sin(v);
        
        return point3d(x, y, z);
    }

    std::string getParameters() const {
        return "Tor: R = " + std::to_string(R) + ", r = " + std::to_string(r);
    }
    
    void setParameters(double newR, double newr) {
        if (newR <= 0 || newr <= 0) {
            throw std::invalid_argument("The radiuses must be positive");
        }
        if (newr >= newR) {
            throw std::invalid_argument("The small radius should be smaller than the large radius.");
        }
        R = newR;
        r = newr;
    }

    void writeSettingsToFile(const std::string& filename = "setting.dat") const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "R=" << R << std::endl;
            file << "r=" << r << std::endl;
            file.close();
            std::cout << "Parameters are written to the file " << filename << std::endl;
        } else {
            std::cerr << "Error opening file!" << std::endl;
        }
    }

    void readSettingsFromFile(const std::string& filename = "setting.dat") {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (line.find("R=") == 0) {
                    R = std::stod(line.substr(2));
                } else if (line.find("r=") == 0) {
                    r = std::stod(line.substr(2));
                }
            }
            file.close();
            std::cout << "Parameters loaded from file " << filename << std::endl;
        } else {
            std::cerr << "File is not found. Default values are used." << std::endl;
        }
    }
};

#endif // TORUS_POINTS_HPP