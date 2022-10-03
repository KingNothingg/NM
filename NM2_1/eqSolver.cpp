#pragma once

#include <cmath>
#include <algorithm>

int iterCount = 0;

double f(double x) {
    return pow(x, 4) - 2 * x - 1;
}

double der(double x) {
    return 4 * pow(x, 3) - 2;
}

double der2(double x) {
    return 12 * pow(x, 2);
}

double phi(double x) {
    return 0.5 * pow(x, 4) - 0.5;
}

double phi_der(double x) {
    return 2 * pow(x,3);
}

double iterations(double l, double r, double eps) {
    iterCount = 0;
    double x_k = (l + r)/2;
    double dx = 1;
    double q = std::max(std::abs(phi_der(l)), std::abs(phi_der(r)));
    double eps_coeff = q / (1 - q);
    while(dx > eps){
        double x_k1 = phi(x_k);
        dx = eps_coeff * std::abs(x_k1 - x_k);
        ++iterCount;
        x_k = x_k1;
    }
    return x_k;
}

double newton(double l, double r, double eps) {
    iterCount = 0;
    double x_k = l;
    if (f(l)*f(r) >=0) {
        return 0;
    }
    if (f(x_k) * der2(x_k) <= 0) {
        x_k = r;
    }
    double dx = 1;
    while (dx > eps) {
        double x_k1 = x_k - f(x_k) / der(x_k);
        dx = std::abs(x_k1 - x_k);
        ++iterCount;
        x_k = x_k1;
    }
    return x_k;
}
