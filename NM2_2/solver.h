//
// Created by kng on 23.05.22.
//

#ifndef NM2_2_SOLVER_H
#define NM2_2_SOLVER_H

#include "lu.cpp"

int iter_count = 0;

const double a = 1;

double phi1(double x1, double x2) {
    return std::sqrt(2 * log10(x2) + 1);
}

double phi2(double x1, double x2) {
    return (x1*x1 + a)/(x1 * a);
}

double phi1_der(double x1, double x2) {
    return 1/(x2 * std::sqrt(log(10)) * std::sqrt(2*log(x2) + log(10)));
}

double phi2_der(double x1, double x2) {
    return (a - 1/(x1*x1*a));
}

double phi(double x1, double x2) {
    return phi1_der(x1, x2) * phi2_der(x1, x2);
}

std::pair<double, double> iter_solve(double l1, double r1, double l2, double r2, double eps) {
    iter_count = 0;
    double x1_k = r1;
    double x2_k = r2;
    double q = -1;
    q = std::max(q, std::abs(phi(l1,r1)));
    q = std::max(q, std::abs(phi(l1,r2)));
    q = std::max(q, std::abs(phi(l2,r1)));
    q = std::max(q, std::abs(phi(l2,r2)));
    double eps_coeff = q/(1-q);
    double dx = 1;
    while (dx > eps) {
        double x1_k1 = phi1(x1_k, x2_k);
        double x2_k1 = phi2(x1_k, x2_k);
        dx = eps_coeff * (std::abs(x1_k1 - x1_k) + std::abs(x2_k1 - x2_k));
        ++iter_count;
        x1_k = x1_k1;
        x2_k = x2_k1;
    }
    return std::make_pair(x1_k, x2_k);
}

double f1(double x1, double x2) {
    return x1*x1 - 2 * log10(x2) - 1;
}

double f2(double x1, double x2) {
    return x1*x1 - a*x1*x2 + a;
}

Matrix<double> Jacobi(double x1, double x2) {
    Matrix<double> result(2);
    result[0][0] = 2 * x1;
    result[0][1] = -2/(x2*log(10));
    result[1][0] = 2 * x1 - a * x2;
    result[1][1] = -a * x1;
    return result;
}

double norm(const std::vector<double> &vec) {
    double res = 0;
    for (auto elem: vec) {
        res = std::max(res, std::abs(elem));
    }
    return res;
}

std::pair<double, double> newton_solve(double x1_0, double x2_0, double eps) {
    iter_count = 0;
    std::vector<double> x_k = {x1_0, x2_0};
    double dx = 1;
    while (dx > eps) {
        double x1 = x_k[0];
        double x2 = x_k[1];
        LU<double> J(Jacobi(x1, x2));
        std::vector<double> f_k = {f1(x1,x2), f2(x1,x2)};
        std::vector<double> d_x = J.solve(f_k);
        std::vector<double> x_k1 = x_k - d_x;
        dx = norm(x_k1 - x_k);
        ++iter_count;
        x_k = x_k1;
    }
    return std::make_pair(x_k[0], x_k[1]);
}


#endif //NM2_2_SOLVER_H
