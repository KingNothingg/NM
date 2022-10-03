#ifndef NM3_5_INTEGRATE_H
#define NM3_5_INTEGRATE_H

#include <cmath>
#include "interpolation.h"

using func = double(double);

double int_rect(double l, double r, double h, func f) {
    double x1 = l;
    double x2 = l + h;
    double res = 0;
    while (x1 < r) {
        res += h * f ((x1 + x2) * 0.5);
        x1 = x2;
        x2 += h;
    }
    return res;
}

double int_trap(double l, double r, double h, func f) {
    double x1 = l;
    double x2 = l + h;
    double res = 0;
    while (x1 < r) {
        res += h * (f(x1) + f(x2));
        x1 = x2;
        x2 += h;
    }
    return res * 0.5;
}

using vec = std::vector<double>;

double int_simp(double l, double r, double h, func f) {
    double x1 = l;
    double x2 = l + h;
    double res = 0;
    while (x1 < r) {
        vec x = {x1, (x1 + x2) * 0.5, x2};
        vec y = {f(x[0]), f(x[1]), f(x[2])};
        Lagrange lagr(x, y);
        res += lagr().integrate(x1, x2);
        x1 = x2;
        x2 += h;
    }
    return res / 3;
}

inline double runge_romberg(double Fh, double Fkh, double k, double p) {
    return (Fh - Fkh) / (std::pow(k, p) - 1.0);
}


#endif //NM3_5_INTEGRATE_H
