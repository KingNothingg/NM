//
// Created by kng on 23.05.22.
//

#ifndef NM3_1_INTERPOLATION_H
#define NM3_1_INTERPOLATION_H

#include "polynom.h"

class Lagrange {
    std::vector<double> x;
    std::vector<double> y;
    int n;

public:
    Lagrange(const std::vector<double> & _x, const std::vector<double> & _y) : x(_x), y(_y), n(x.size()) {};

    Polynom operator() () {
        Polynom result(std::vector<double> ({0}));
        for (int i = 0; i < n; ++i) {
            Polynom li(std::vector<double>({1})); //Лагранжев многочлен влияния
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                Polynom xij(std::vector<double>({-x[j], 1})); // x - x_i
                li = li * xij;
                li = li / (x[i] - x[j]);
            }
            result = result + y[i] * li; // Summ(f_i * П(x - x_i)/(x_i - x_j))
        }
        return result;
    }
};

class Newton {
private:
    std::vector<double> x;
    std::vector<double> y;
    int n;

    std::vector<std::vector<double>> memo;
    std::vector<std::vector<bool>> done;

    double f(int l, int r) {
        if (done[l][r]) {
            return memo[l][r];
        }
        done[l][r] = true;
        double res;
        if (l + 1 == r) {
            res = (y[l] - y[r]) / (x[l] - x[r]); // Если разделенная разность 1го порядка
        } else {
            res = (f(l, r - 1) - f(l + 1, r)) / (x[l] - x[r]);
        }
        return memo[l][r] = res;
    }
public:
    Newton(const std::vector<double> & _x, const std::vector<double> & _y) : x(_x), y(_y), n(x.size()) {
        memo.resize(n, std::vector<double>(n));
        done.resize(n, std::vector<bool> (n));
    };

    Polynom operator() () {
        Polynom res(std::vector<double>({y[0]}));
        Polynom prod(std::vector<double>({-x[0], 1})); // x - x_0
        int r = 0;
        for (int i = 1; i < n; ++i) {
            res = res + f(0, ++r) * prod;
            prod = prod * Polynom(std::vector<double>({-x[i], 1})); // (x - x_i)*(x - x_(i+1)).... Накапливается произведение
        }
        return res;
    }
};

#endif //NM3_1_INTERPOLATION_H
