// curve3d.cpp
#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <cmath>
#include <iomanip>
#include <stdexcept>

#include "curves3d.h"



Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

Curve3D::~Curve3D() = default;
// --- Circle---
Circle::Circle(double r) : radius(r) {
    if (r <= 0.0) throw std::invalid_argument("Radius must be positive");
}

Point3D Circle::point(double t) const {
    return Point3D(radius * std::cos(t), radius * std::sin(t), 0.0);
}

Point3D Circle::derivative(double t) const {
    return Point3D(-radius * std::sin(t), radius * std::cos(t), 0.0);
}

// --- Ellipse ---
Ellipse::Ellipse(double a, double b) : a(a), b(b) {
    if (a <= 0.0 || b <= 0.0)
        throw std::invalid_argument("Ellipse axes must be positive");
}

Point3D Ellipse::point(double t) const {
    return Point3D(a * std::cos(t), b * std::sin(t), 0.0);
}

Point3D Ellipse::derivative(double t) const {
    return Point3D(-a * std::sin(t), b * std::cos(t), 0.0);
}

// --- Helix ---
Helix::Helix(double r, double h) : radius(r), step(h) {
    if (r <= 0.0 || h <= 0.0)
        throw std::invalid_argument("Helix radius and step must be positive");
}

Point3D Helix::point(double t) const {
    return Point3D(radius * std::cos(t), radius * std::sin(t), step * t / (2.0 * M_PI));
}

Point3D Helix::derivative(double t) const {
    return Point3D(-radius * std::sin(t), radius * std::cos(t), step / (2.0 * M_PI));
}



