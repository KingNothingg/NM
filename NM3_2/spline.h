//
// Created by kng on 23.05.22.
//

#ifndef NM3_2_SPLINE_H
#define NM3_2_SPLINE_H

#include <cmath>
#include "tridiag.cpp"

class Spline {
    int n;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> a, b, c, d;

    void build() {
        std::vector<double> h(n + 1);
        h[0] = NAN;
        for (int i = 1; i <= n; ++i) {
            h[i] = x[i] - x[i - 1];
        }
        std::vector<double> eq_a(n - 1), eq_b(n - 1), eq_c(n - 1), eq_d(n - 1);
        for (int i = 2; i <= n; ++i) { //Система h_i-1*c_i-1 + 2(h_i-1 + h_i)*c_i + h_i*c_i+1 = 3[(f_i - f_i-1)/h_i - (f_i-1 - f_i-2)/h_i-1]
            eq_a[i - 2] = h[i - 1];
            eq_b[i - 2] = 2 * (h[i - 1] + h[i]);
            eq_c[i - 2] = h[i];
            eq_d[i - 2] = 3.0 * ((y[i] - y[i - 1]) / h[i] - (y[i - 1] - y[i - 2]) / h[i - 1]);
        }
        eq_a[0] = 0;
        eq_c.back() = 0;
        Tridiag<double> system(eq_a, eq_b, eq_c);
        std::vector<double> solution = system.Solve(eq_d);
        for (int i = 2; i <= n; ++i) {
            c[i] = solution[i - 2];
        }
        for (int i = 1; i <= n; ++i) {
            a[i] = y[i - 1];
        }
        for (int i = 1; i < n; ++i) {
            b[i] = (y[i] - y[i - 1]) / h[i] - h[i] * (c[i + 1] + 2.0 * c[i]) / 3.0;
            d[i] = (c[i + 1] - c[i]) / (3.0 * h[i]);
        }
        c[1] = 0.0;
        b[n] = (y[n] - y[n - 1]) / h[n] - (2.0 / 3.0) * h[n] * c[n];
        d[n] = -c[n] / (3.0 * h[n]);
    }
public:
    Spline(const std::vector<double> &_x, const std::vector<double> &_y) {
        x = _x;
        y = _y;
        n = x.size() - 1;
        a.resize(n + 1);
        b.resize(n + 1);
        c.resize(n + 1);
        d.resize(n + 1);
        build();
    }

    friend std::ostream & operator << (std::ostream &out, const Spline &spline) {
        for (int i = 1; i <= spline.n; ++i) {
            out << "i = " << i << ", a = " << spline.a[i] << ", b = " << spline.b[i] << ", c = " << spline.c[i] << ",d = " << spline.d[i] << '\n';
        }
        return out;
    }

    double operator () (double x0) {
        for (int i = 1; i <= n; ++i) {
            if (x[i - 1] <= x0 && x0 <= x[i]) {
                double x1 = x0 - x[i - 1];
                double x2 = x1 * x1;
                double x3 = x1 * x1 * x1;
                return a[i] + b[i] * x1 + c[i] * x2 + d[i] * x3;
            }
        }
        return NAN;
    }
};

#endif //NM3_2_SPLINE_H
