/**
 * @file main.cpp
 * @brief Основная программа для генерации и управления точками на торе
 * @author Клим
 * 
 * Программа предоставляет интерактивное меню для работы с точками на поверхности тора:
 * - Генерация случайных точек
 * - Просмотр и добавление точек
 * - Сохранение и загрузка данных
 */

#include "torus_points.hpp"
#include <limits>

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении, 1 при ошибке
 * 
 * Функция реализует основной цикл программы с интерактивным меню для управления точками тора
 */
int main() {
    point3d* points = nullptr;  ///< Указатель на динамический массив точек
    int pointCount = 0;          ///< Текущее количество точек в массиве
    int arraySize = 0;           ///< Размер выделенной памяти для массива
    int choice;                  ///< Выбор пользователя в меню
    
    std::cout << "=== Torus Points Generator (Upper Half) ===" << std::endl;
    
    // Запрос параметров области
    double R, r;
    std::cout << "Enter major torus radius (R): ";
    std::cin >> R;
    std::cout << "Enter minor torus radius (r): ";
    std::cin >> r;
    
    // Создание генератора с пользовательскими параметрами
    TorusPointGenerator generator;
    try {
        generator.setParameters(R, r);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Program terminated." << std::endl;
        return 1;
    }
    
    // Вывод параметров области
    std::cout << "\nRegion parameters: " << generator.getParameters() << std::endl;
    
    // Основной цикл меню
    do {
        std::cout << "1. Fill the array with random points" << std::endl;  ///< Заполнить массив случайными точками
        std::cout << "2. Show i point" << std::endl;                       ///< Показать i-ю точку
        std::cout << "3. Show the point coordinate" << std::endl;          ///< Показать координату точки
        std::cout << "4. Add a point manually" << std::endl;               ///< Добавить точку вручную
        std::cout << "5. Write an array to a file" << std::endl;           ///< Записать массив в файл
        std::cout << "6. Show area parameters" << std::endl;               ///< Показать параметры области
        std::cout << "7. Write the parameters to a file" << std::endl;     ///< Записать параметры в файл
        std::cout << "8. Download parameters from a file" << std::endl;    ///< Загрузить параметры из файла
        std::cout << "0. Exit" << std::endl;                               ///< Выход из программы
        std::cout << "Select an action: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                // Заполнение массива случайными точками
                int K;
                std::cout << "Enter number of points: ";
                std::cin >> K;
                
                if (K < 1) {
                    std::cout << "Invalid number!" << std::endl;
                    break;
                }
                
                // Освобождаем старую память, если была выделена
                if (points != nullptr) {
                    delete[] points;
                }
                
                // Выделяем память под массив точек
                points = new point3d[K];
                arraySize = K;
                pointCount = K;
                
                // Заполняем массив случайными точками
                for (int i = 0; i < K; ++i) {
                    points[i] = generator.rnd();
                }
                std::cout << "Generated " << K << " points." << std::endl;
                break;
            }
                
            case 2: {
                // Показать i-ю точку
                if (points == nullptr || pointCount == 0) {
                    std::cout << "Array is empty!" << std::endl;
                    break;
                }
                
                int index;
                std::cout << "Enter point index (0-" << pointCount - 1 << "): ";
                std::cin >> index;
                
                if (index >= 0 && index < pointCount) {
                    std::cout << "Point " << index << ": ";
                    points[index].print();
                } else {
                    std::cout << "Invalid index!" << std::endl;
                }
                break;
            }
                
            case 3: {
                // Показать координату точки
                if (points == nullptr || pointCount == 0) {
                    std::cout << "Array is empty!" << std::endl;
                    break;
                }
                
                int index;
                char coord;
                std::cout << "Enter point index (0-" << pointCount - 1 << "): ";
                std::cin >> index;
                std::cout << "Choose coordinate (x, y, z): ";
                std::cin >> coord;
                
                if (index >= 0 && index < pointCount) {
                    switch (coord) {
                        case 'x':
                            std::cout << "X = " << points[index].getBackX() << std::endl;
                            break;
                        case 'y':
                            std::cout << "Y = " << points[index].getBackY() << std::endl;
                            break;
                        case 'z':
                            std::cout << "Z = " << points[index].getBackZ() << std::endl;
                            break;
                        default:
                            std::cout << "Invalid coordinate!" << std::endl;
                    }
                } else {
                    std::cout << "Invalid index!" << std::endl;
                }
                break;
            }
                
            case 4: {
                // Добавление точки вручную
                double x, y, z;
                std::cout << "Enter point coordinates:" << std::endl;
                std::cout << "X: "; std::cin >> x;
                std::cout << "Y: "; std::cin >> y;
                std::cout << "Z: "; std::cin >> z;
                
                // Проверяем, есть ли место в массиве
                if (pointCount < arraySize) {
                    // Есть место - добавляем
                    points[pointCount] = point3d(x, y, z);
                    pointCount++;
                } else {
                    // Нужно перевыделить память
                    int newSize = (arraySize == 0) ? 1 : arraySize * 2;
                    if (newSize > 10000) newSize = 10000;
                    
                    point3d* newPoints = new point3d[newSize];
                    
                    // Копируем старые точки
                    for (int i = 0; i < pointCount; i++) {
                        newPoints[i] = points[i];
                    }
                    
                    // Добавляем новую точку
                    newPoints[pointCount] = point3d(x, y, z);
                    pointCount++;
                    arraySize = newSize;
                    
                    // Освобождаем старую память и присваиваем новый указатель
                    if (points != nullptr) {
                        delete[] points;
                    }
                    points = newPoints;
                }
                
                std::cout << "Point added. Total points: " << pointCount << std::endl;
                break;
            }
                
            case 5: {
                // Запись массива в файл
                if (points == nullptr || pointCount == 0) {
                    std::cout << "Array is empty!" << std::endl;
                    break;
                }
                
                std::ofstream file("points.txt");
                if (file.is_open()) {
                    for (int i = 0; i < pointCount; i++) {
                        file << points[i].x << " " << points[i].y << " " << points[i].z << std::endl;
                    }
                    file.close();
                    std::cout << "Array written to file points.txt" << std::endl;
                } else {
                    std::cerr << "File opening error!" << std::endl;
                }
                break;
            }
                
            case 6: {
                // Показать параметры области
                std::cout << generator.getParameters() << std::endl;
                break;
            }
                
            case 7: {
                // Запись параметров в файл
                generator.writeSettingsToFile();
                break;
            }
                
            case 8: {
                // Загрузка параметров из файла
                generator.readSettingsFromFile();
                break;
            }
                
            case 0: {
                std::cout << "Program exit." << std::endl;
                break;
            }
                
            default: {
                std::cout << "Invalid choice!" << std::endl;
                break;
            }
        }
        
    } while (choice != 0);
    
    // Освобождаем память перед выходом
    if (points != nullptr) {
        delete[] points;
    }
    
    return 0;
}