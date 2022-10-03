//
// Created by kng on 23.05.22.
//

#ifndef NM3_3_MNK_H
#define NM3_3_MNK_H

#include <functional>
#include "polynom.h"
#include "lu.cpp"

class MNK {
    int n;
    std::vector<double> x, y;
    int m;
    std::vector<double> a;
    std::vector<std::function<double(double)>> phi;

    void build() {
        Matrix<double> lhs(n, m);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                lhs[i][j] = phi[j](x[i]);
            }
        }
        Matrix<double> t = lhs.t();
        LU<double> lhs_lu(t * lhs);
        std::vector<double> rhs = t * y;
        a = lhs_lu.solve(rhs);
    }

    double get(double x0) {
        double res = 0.0;
        for (int i = 0; i < m; ++i) {
            res += a[i] * phi[i](x0);
        }
        return res;
    }

public:

    MNK(const std::vector<double> &_x, const std::vector<double> &_y, const std::vector<std::function<double(double)>> _phi) {
        n = _x.size();
        x = _x;
        y = _y;
        m = _phi.size();
        a.resize(m);
        phi = _phi;
        build();
    }

    friend std::ostream & operator << (std::ostream &out, const MNK &item) {
        for (int i = 0; i < item.m; ++i) {
            if (i) {
                out << " ";
            }
            out << item.a[i];
        }
        return out;
    }

    double error() {
        double res = 0;
        for (int i = 0; i < n; ++i) {
            res += std::pow(get(x[i]) - y[i], 2.0);
        }
        return res;
    }

    double operator () (double x0) {
        return get(x0);
    }
};

#endif //NM3_3_MNK_H
