#include "torus_points.hpp"
#include <limits>

int main() {
    TorusPointGenerator generator;
    std::vector<point3d> points;
    int choice;
    
    std::cout << "=== The point generator in the upper half of the torus ===" << std::endl;
    
    // Запрос параметров области
    double R, r;
    std::cout << "Enter the large radius of the torus (R): ";
    std::cin >> R;
    std::cout << "Enter the small radius of the torus (r): ";
    std::cin >> r;
    
    try {
        generator.setParameters(R, r);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Default values are used: R=5.0, r=2.0" << std::endl;
    }
    
    // Вывод параметров области
    std::cout << "\nArea Parameters: " << generator.getParameters() << std::endl;
    
    // Основной цикл меню
    do {
        std::cout << "1. Fill the array with random points" << std::endl;  //Заполнить массив случайными точками
        std::cout << "2. Show i point" << std::endl;                       //Показать i-ю точку
        std::cout << "3. Show the point coordinate" << std::endl;          //Показать координату точки
        std::cout << "4. Add a point manually" << std::endl;               //Добавить точку вручную
        std::cout << "5. Write an array to a file" << std::endl;           //Записать массив в файл
        std::cout << "6. Show area parameters" << std::endl;               //Показать параметры области
        std::cout << "7. Write the parameters to a file" << std::endl;     //Записать параметры в файл
        std::cout << "8. Download parameters from a file" << std::endl;    //Загрузить параметры из файла
        std::cout << "0. Exit" << std::endl;
        std::cout << "Select an action: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                // Заполнение массива случайными точками
                int K;
                std::cout << "Enter the number of points: ";
                std::cin >> K;
                
                if (K < 1) {
                    std::cout << "Incorrect quantity!" << std::endl;
                    break;
                }
                
                points.clear();
                for (int i = 0; i < K; ++i) {
                    points.push_back(generator.rnd());
                }
                std::cout << "Generated " << K << " points." << std::endl;
                break;
            }
                
            case 2: {
                // Показать i-ю точку
                if (points.empty()) {
                    std::cout << "Massive is empty" << std::endl;
                    break;
                }
                
                int index;
                std::cout << "Enter the point's index (0-" << points.size() - 1 << "): ";
                std::cin >> index;
                
                if (index >= 0 && index < points.size()) {
                    std::cout << "Point " << index << ": ";
                    points[index].print();
                } else {
                    std::cout << "Incorrect index!" << std::endl;
                }
                break;
            }
                
            case 3: {
                // Показать координату точки
                if (points.empty()) {
                    std::cout << "Massive is empty!" << std::endl;
                    break;
                }
                
                int index;
                char coord;
                std::cout << "Enter the point's index (0-" << points.size() - 1 << "): ";
                std::cin >> index;
                std::cout << "Select a coordinate (x, y, z): ";
                std::cin >> coord;
                
                if (index >= 0 && index < points.size()) {
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
                            std::cout << "Incorrect coordinate!" << std::endl;
                    }
                } else {
                    std::cout << "Incorrect index!" << std::endl;
                }
                break;
            }
                
            case 4: {
                // Добавление точки вручную
                double x, y, z;
                std::cout << "Enter the coordinates of the point:" << std::endl;
                std::cout << "X: "; std::cin >> x;
                std::cout << "Y: "; std::cin >> y;
                std::cout << "Z: "; std::cin >> z;
                
                points.push_back(point3d(x, y, z));
                std::cout << "The point has been added. Total points: " << points.size() << std::endl;
                break;
            }
                
            case 5: {
                // Запись массива в файл
                std::ofstream file("points.txt");
                if (file.is_open()) {
                    for (const auto& p : points) {
                        file << p.x << " " << p.y << " " << p.z << std::endl;
                    }
                    file.close();
                    std::cout << "The array is written to a file points.txt" << std::endl;
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
                std::cout << "Exiting the program." << std::endl;
                break;
            }
                
            default: {
                std::cout << "Wrong choice!" << std::endl;
                break;
            }
        }
        
    } while (choice != 0);
    
    return 0;
}