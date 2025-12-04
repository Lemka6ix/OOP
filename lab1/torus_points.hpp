#ifndef TORUS_POINTS_HPP
#define TORUS_POINTS_HPP

#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <string>

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
    TorusPointGenerator() {
        std::random_device rd;
        generator.seed(rd());
        R = 0.0;
        r = 0.0;
    }

    /**
     * @brief Генерация случайной точки в объеме верхней половины тора
     * @return Объект point3d со случайными координатами внутри тора
     * 
     * Генерирует точки не только на поверхности, но и внутри всего объема
     * верхней половины тора (бублика). Используется параметризация тора
     * с дополнительным случайным параметром для радиуса внутри трубки.
     */
    point3d rnd() {
        if (R <= 0 || r <= 0) {
            throw std::runtime_error("Input parameters: R and r.");
        }
        
        // Используем параметрические уравнения тора
        // u - угол вокруг оси тора (0 до 2π)
        // v - угол вокруг трубки (0 до π для верхней половины)
        // s - случайный радиус внутри трубки (0 до r)
        
        std::uniform_real_distribution<double> distU(0.0, 2.0 * M_PI);
        std::uniform_real_distribution<double> distV(0.0, M_PI);  // Только верхняя половина
        std::uniform_real_distribution<double> distS(0.0, r);    // Радиус внутри трубки
        
        double u = distU(generator);
        double v = distV(generator);
        double s = distS(generator);  // Случайный радиус внутри трубки
        
        // Параметрические уравнения тора с учетом внутреннего радиуса
        double x = (R + s * cos(v)) * cos(u);
        double y = (R + s * cos(v)) * sin(u);
        double z = s * sin(v);  // Для верхней половины sin(v) >= 0 при v ∈ [0, π]
        
        return point3d(x, y, z);
    }

    std::string getParameters() const {
        return "Tor: R = " + std::to_string(R) + ", r = " + std::to_string(r);
    }
  
    void setParameters(double newR, double newr) {
        if (newR <= 0 || newr <= 0) {
            throw std::invalid_argument("Radiuses should be positive");
        }
        if (newr >= newR) {
            throw std::invalid_argument("r sholid be < R");
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
            std::cout << "The parameters are written to the file " << filename << std::endl;
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
            std::cerr << "File not found. Using default values." << std::endl;
        }
    }
};

#endif