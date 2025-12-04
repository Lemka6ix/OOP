/**
 * @file torus_points.hpp
 * @brief Заголовочный файл, содержащий структуру точки и класс для генерации точек тора
 * @author Клим
 */

#ifndef TORUS_POINTS_HPP
#define TORUS_POINTS_HPP

#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <string>

/**
 * @brief Структура для представления точки в трехмерном пространстве
 * 
 * Структура хранит координаты x, y, z точки и предоставляет методы для их получения и вывода
 */
struct point3d {
    double x, y, z; ///< Координаты точки
    
    /**
     * @brief Конструктор структуры point3d
     * @param x Координата X (по умолчанию 0.0)
     * @param y Координата Y (по умолчанию 0.0)
     * @param z Координата Z (по умолчанию 0.0)
     */
    point3d(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    /**
     * @brief Вывод координат точки в консоль
     */
    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    /**
     * @brief Получение координаты X
     * @return Значение координаты X
     */
    double getBackX() const { return x; }
    
    /**
     * @brief Получение координаты Y
     * @return Значение координаты Y
     */
    double getBackY() const { return y; }
    
    /**
     * @brief Получение координаты Z
     * @return Значение координаты Z
     */
    double getBackZ() const { return z; }
};

/**
 * @brief Класс для генерации случайных точек в верхней половине тора
 * 
 * Класс позволяет генерировать точки, равномерно распределенные в верхней половине торической поверхности
 */
class TorusPointGenerator {
private:
    double R;  ///< Большой радиус тора (расстояние от центра тора до центра трубки)
    double r;  ///< Малый радиус тора (радиус трубки)
    std::mt19937 generator;  ///< Генератор случайных чисел Mersenne Twister
    
public:
    /**
     * @brief Конструктор класса TorusPointGenerator
     * 
     * Инициализирует генератор случайных чисел и устанавливает начальные значения радиусов в 0
     */
    TorusPointGenerator() {
        std::random_device rd;
        generator.seed(rd());
        R = 0.0;
        r = 0.0;
    }

    /**
     * @brief Генерация случайной точки в верхней половине тора
     * @return Объект point3d со случайными координатами на поверхности тора
     * @throws std::runtime_error если параметры R и r не установлены
     * 
     * Использует параметрические уравнения тора для генерации случайных точек:
     * x = (R + r*cos(v)) * cos(u)
     * y = (R + r*cos(v)) * sin(u)
     * z = r*sin(v)
     * где u ∈ [0, 2π), v ∈ [0, π)
     */
    point3d rnd() {
        if (R <= 0 || r <= 0) {
            throw std::runtime_error("Input parameters: R and r.");
        }
        
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

    /**
     * @brief Получение строкового представления параметров тора
     * @return Строка с параметрами тора в формате "Tor: R = X, r = Y"
     */
    std::string getParameters() const {
        return "Tor: R = " + std::to_string(R) + ", r = " + std::to_string(r);
    }
  
    /**
     * @brief Установка параметров тора
     * @param newR Большой радиус тора
     * @param newr Малый радиус тора
     * @throws std::invalid_argument если радиусы некорректны
     * 
     * Проверяет, что радиусы положительные и что малый радиус меньше большого
     */
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

    /**
     * @brief Запись параметров тора в файл
     * @param filename Имя файла для сохранения параметров (по умолчанию "setting.dat")
     * 
     * Записывает параметры в формате:
     * R=значение
     * r=значение
     */
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

    /**
     * @brief Чтение параметров тора из файла
     * @param filename Имя файла с параметрами (по умолчанию "setting.dat")
     * 
     * Читает параметры из файла в формате:
     * R=значение
     * r=значение
     */
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