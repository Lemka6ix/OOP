#include <iostream>
#include <vector>
#include <fstream>
#include "point3d.hpp"
#include "TorPointGenerator.hpp"
#ifdef WITH_MATHGL
#include <mg12/mgl.h>
#endif

int main() {
    double R, r;
    std::cout << "Введите параметры тора R и r: ";
    std::cin >> R >> r;

    TorPointGenerator generator(R, r);
    generator.saveSettings();

    int K;
    std::cout << "Введите количество точек K: ";
    std::cin >> K;

    std::vector<point3d> points;
    for (int i = 0; i<K; ++i) {
        points.push_back(generator.rnd());
    }
    int choice;
    do {
        std::cout << "\n1. Вывести точку\n2. Вывести координату\n3. Добавить точку\n4. Сохранить в файл\n5. Визуализировать\n0. Выход\nВыберите: ";
        std::cin >> choice;
        if (choice == 1) {
            int index;
            std::cout << "Введите индекс точки: ";
            std::cin >> index;
            if (index >= 0 && index < points.size()) {
                points[index].print();
            } else {
                std::cout << "Неверный индекс!" << std::endl;
            }
        } else if (choice == 2) {
            int index;
            char coord;
            std::cout << "Введите индекс точки и координату (x, y, z): ";
            std::cin >> index >> coord;
            if (index >= 0 && index < points.size()) {
                switch (coord) {
                    case 'x': std::cout << points[index].getBackX() << std::endl; break;
                    case 'y': std::cout << points[index].getBackY() << std::endl; break;
                    case 'z': std::cout << points[index].getBackZ() << std::endl; break;
                }
            } else {
                std::cout << "Неверный индекс!" << std::endl;
            }
        } else if (choice == 3) {
            double x, y, z;
            std::cout << "Введите координаты (x, y, z): ";
            std::cin >> x >> y >> z;
            points.emplace_back(x, y, z); 
        } else if (choice == 3) {
            std::ofstream file("points.txt");
            for (const auto& p : points) {
                file << p.getBackX << " " << p.getBackY << " " << p.getBackZ << "\n";
            }
            file.close();
            std::cout << "Файл сохранен." << std::endl;
        }
    }
}