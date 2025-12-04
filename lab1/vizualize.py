import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_points_from_file(filename):
    """Чтение точек из файла"""
    points = []
    with open(filename, 'r') as f:
        for line in f:
            if line.strip():
                try:
                    x, y, z = map(float, line.strip().split())
                    points.append([x, y, z])
                except ValueError:
                    continue
    return np.array(points)

def create_torus_surface(R, r):
    """Создание поверхности тора для визуализации"""
    u = np.linspace(0, 2 * np.pi, 50)
    v = np.linspace(0, np.pi, 25)  # Только верхняя половина
    U, V = np.meshgrid(u, v)
    
    X = (R + r * np.cos(V)) * np.cos(U)
    Y = (R + r * np.cos(V)) * np.sin(U)
    Z = r * np.sin(V)
    
    return X, Y, Z

def read_settings_from_file(filename="setting.dat"):
    """Чтение параметров тора из файла настроек"""
    R, r = 0.0, 0.0
    try:
        with open(filename, 'r') as f:
            for line in f:
                if line.startswith("R="):
                    R = float(line.strip()[2:])
                elif line.startswith("r="):
                    r = float(line.strip()[2:])
    except FileNotFoundError:
        print(f"Файл {filename} не найден!")
        return None, None
    
    if R <= 0 or r <= 0:
        print("Ошибка: параметры тора не заданы или некорректны в файле setting.dat")
        return None, None
    
    return R, r

def visualize_points():
    """Визуализация точек и поверхности тора"""
    try:
        points = read_points_from_file('points.txt')
    except FileNotFoundError:
        print("Файл points.txt не найден!")
        print("Сначала запустите C++ программу и сохраните точки в файл.")
        return
    
    # Чтение параметров тора
    R, r = read_settings_from_file()
    if R is None or r is None:
        print("Невозможно визуализировать: параметры тора не заданы")
        return
    
    # Создание фигуры
    fig = plt.figure(figsize=(10, 8))
    
    # 3D визуализация
    ax = fig.add_subplot(111, projection='3d')
    
    # Создание поверхности тора
    X, Y, Z = create_torus_surface(R, r)
    
    # Отображение поверхности (полупрозрачной)
    ax.plot_surface(X, Y, Z, alpha=0.3, color='blue', rstride=1, cstride=1, label='Поверхность тора')
    
    # Отображение точек
    if len(points) > 0:
        ax.scatter(points[:, 0], points[:, 1], points[:, 2], 
                   c='red', s=10, alpha=0.6, label='Сгенерированные точки')
    
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title(f'Точки в верхней половине тора (R={R}, r={r})')
    ax.legend()
    
    plt.show()
    
    # Статистика
    print("=" * 50)
    print("СТАТИСТИКА:")
    print("=" * 50)
    print(f"Параметры тора: R = {R}, r = {r}")
    print(f"Всего точек: {len(points)}")
    if len(points) > 0:
        print(f"Диапазон координат X: [{points[:, 0].min():.2f}, {points[:, 0].max():.2f}]")
        print(f"Диапазон координат Y: [{points[:, 1].min():.2f}, {points[:, 1].max():.2f}]")
        print(f"Диапазон координат Z: [{points[:, 2].min():.2f}, {points[:, 2].max():.2f}]")
        print(f"Среднее Z: {points[:, 2].mean():.2f} (ожидается положительное для верхней половины)")

if __name__ == "__main__":
    visualize_points()