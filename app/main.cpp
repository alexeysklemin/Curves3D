#include <iostream>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <cmath>
#include <iomanip>

#include "curves3d.h"


// --- Helper ---
void printPoint(const Point3D& p) {
    std::cout << std::fixed << std::setprecision(4)
        << "(" << p.x << ", " << p.y << ", " << p.z << ")";
}

// --- Main ---
int main() {
    // Используем точное значение PI, независимо от M_PI
    constexpr double PI = 3.14159265358979323846;
    const double t = PI / 4.0;

    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(1.0, 10.0);
    std::uniform_int_distribution<int> typeDist(0, 2);

    // 1. Создаём контейнер случайных кривых
    std::vector<std::unique_ptr<Curve3D>> curves;
    const int N = 10;

    for (int i = 0; i < N; ++i) {
        double r1 = dist(gen);
        double r2 = dist(gen);
        switch (typeDist(gen)) {
        case 0: curves.push_back(std::make_unique<Circle>(r1)); break;
        case 1: curves.push_back(std::make_unique<Ellipse>(r1, r2)); break;
        case 2: curves.push_back(std::make_unique<Helix>(r1, r2)); break;
        }
    }

    // 2. Выводим точки и производные при t = PI/4
    std::cout << "Points and derivatives at t = PI/4:\n";
    for (size_t i = 0; i < curves.size(); ++i) {
        Point3D p = curves[i]->point(t);
        Point3D d = curves[i]->derivative(t);
        std::cout << "Curve " << i << ": point = ";
        printPoint(p);
        std::cout << ", derivative = ";
        printPoint(d);
        std::cout << "\n";
    }

    // 3. Фильтруем только окружности (через указатели на существующие объекты)
    std::vector<const Circle*> circles;
    for (const auto& curve : curves) {
        if (const Circle* c = dynamic_cast<const Circle*>(curve.get())) {
            circles.push_back(c);
        }
    }

    // 4. Сортируем по радиусу
    std::sort(circles.begin(), circles.end(),
        [](const Circle* a, const Circle* b) {
            return a->getRadius() < b->getRadius();
        });

    // 5. Сумма радиусов
    double totalRadius = 0.0;
    for (const Circle* c : circles) {
        totalRadius += c->getRadius();
    }

    std::cout << "\nFound " << circles.size() << " circles.\n";
    std::cout << "Total sum of radii: " << std::fixed << std::setprecision(4)
        << totalRadius << "\n";

    return 0;
}