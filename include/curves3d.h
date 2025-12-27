#ifndef CURVES3D_H
#define CURVES3D_H

#if defined(_WIN32) || defined(_WIN64)
  #if defined(CURVES_LIBRARY)
    #define CURVES_API __declspec(dllexport)
  #else
    #define CURVES_API __declspec(dllimport)
  #endif
#else
  #define CURVES_API
#endif

struct CURVES_API Point3D {
    double x, y, z;
    Point3D(double x = 0.0, double y = 0.0, double z = 0.0);
};

class CURVES_API Curve3D {
public:
    virtual ~Curve3D();
    virtual Point3D point(double t) const = 0;
    virtual Point3D derivative(double t) const = 0;
};

class CURVES_API Circle : public Curve3D {
    double radius;
public:
    Circle(double r);
    Point3D point(double t) const override;
    Point3D derivative(double t) const override;
    double getRadius() const { return radius; }
};

class CURVES_API Ellipse : public Curve3D {
    double a, b;
public:
    Ellipse(double a, double b);
    Point3D point(double t) const override;
    Point3D derivative(double t) const override;
};

class CURVES_API Helix : public Curve3D {
    double radius, step;
public:
    Helix(double r, double h);
    Point3D point(double t) const override;
    Point3D derivative(double t) const override;
};

#endif // CURVES3D_H