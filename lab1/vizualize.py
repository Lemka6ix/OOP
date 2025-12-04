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

def create_torus_surface(R=5.0, r=2.0):
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
    R, r = 5.0, 2.0  # значения по умолчанию
    try:
        with open(filename, 'r') as f:
            for line in f:
                if line.startswith("R="):
                    R = float(line.strip()[2:])
                elif line.startswith("r="):
                    r = float(line.strip()[2:])
    except FileNotFoundError:
        print(f"Файл {filename} не найден, используются значения по умолчанию")
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
    
    # Создание фигуры
    fig = plt.figure(figsize=(14, 10))
    
    # 3D визуализация
    ax1 = fig.add_subplot(221, projection='3d')
    
    # Создание поверхности тора
    X, Y, Z = create_torus_surface(R, r)
    
    # Отображение поверхности (полупрозрачной)
    ax1.plot_surface(X, Y, Z, alpha=0.3, color='blue', rstride=1, cstride=1, label='Поверхность тора')
    
    # Отображение точек
    if len(points) > 0:
        scatter = ax1.scatter(points[:, 0], points[:, 1], points[:, 2], 
                   c='red', s=10, alpha=0.6, label='Сгенерированные точки')
    
    ax1.set_xlabel('X')
    ax1.set_ylabel('Y')
    ax1.set_zlabel('Z')
    ax1.set_title(f'3D визуализация точек в торе (R={R}, r={r})')
    ax1.legend()
    
    # Проекция на плоскость XY
    ax2 = fig.add_subplot(222)
    if len(points) > 0:
        ax2.scatter(points[:, 0], points[:, 1], c='red', s=10, alpha=0.6)
    ax2.set_xlabel('X')
    ax2.set_ylabel('Y')
    ax2.set_title('Проекция на плоскость XY')
    ax2.grid(True, alpha=0.3)
    ax2.axis('equal')
    
    # Проекция на плоскость XZ
    ax3 = fig.add_subplot(223)
    if len(points) > 0:
        ax3.scatter(points[:, 0], points[:, 2], c='red', s=10, alpha=0.6)
    ax3.set_xlabel('X')
    ax3.set_ylabel('Z')
    ax3.set_title('Проекция на плоскость XZ')
    ax3.grid(True, alpha=0.3)
    ax3.axis('equal')
    
    # Проекция на плоскость YZ
    ax4 = fig.add_subplot(224)
    if len(points) > 0:
        ax4.scatter(points[:, 1], points[:, 2], c='red', s=10, alpha=0.6)
    ax4.set_xlabel('Y')
    ax4.set_ylabel('Z')
    ax4.set_title('Проекция на плоскость YZ')
    ax4.grid(True, alpha=0.3)
    ax4.axis('equal')
    
    plt.tight_layout()
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