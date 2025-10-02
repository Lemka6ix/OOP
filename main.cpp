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
            std::cout
        }
    }
}