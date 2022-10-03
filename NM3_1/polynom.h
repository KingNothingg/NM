//
// Created by kng on 23.05.22.
//

#ifndef NM3_1_POLYNOM_H
#define NM3_1_POLYNOM_H

#include <iostream>
#include <vector>

class Polynom {
private:
    std::vector<double> data;
    int n;

    constexpr static double eps = 1e-9;

public:
    Polynom() : data(1), n(1) {}

    Polynom(int _n) : data(_n), n(_n) {}

    Polynom(const std::vector<double> &c) : data(c), n(data.size()) {}

    int size() const {
        return n;
    }

    double & operator[](int ind) {
        return data[ind];
    }

    const double & operator[](int ind) const {
        return data[ind];
    }

    friend Polynom operator+(const Polynom &lhs, const Polynom &rhs) {
        Polynom res(std::max(lhs.size(), rhs.size()));
        for (int i = 0; i < lhs.size(); ++i) {
            res[i] += lhs[i];
        }
        for (int i = 0; i < rhs.size(); ++i) {
            res[i] += rhs[i];
        }
        return res;
    }

    friend Polynom operator-(const Polynom &lhs, const Polynom &rhs) {
        Polynom res(std::max(lhs.size(), rhs.size()));
        for (int i = 0; i < lhs.size(); ++i) {
            res[i] += lhs[i];
        }
        for (int i = 0; i < rhs.size(); ++i) {
            res[i] -= rhs[i];
        }
        return res;
    }

    friend Polynom operator*(double c, const Polynom &p) {
        Polynom res(p);
        for (int i = 0; i < res.size(); ++i) {
            res[i] *= c;
        }
        return res;
    }

    friend Polynom operator/(const Polynom &p, double c) {
        Polynom res(p);
        for (int i = 0; i < res.size(); ++i) {
            res[i] /= c;
        }
        return res;
    }

    friend Polynom operator*(const Polynom &lhs, const Polynom &rhs) {
        Polynom res(lhs.size() + rhs.size());
        for (int i = 0; i < lhs.size(); ++i) {
            for (int j = 0; j < rhs.size(); ++j) {
                res[i + j] += lhs[i] * rhs[j];
            }
        }
        while (res.n > 1 && std::abs(res.data.back()) > eps) {
            res.data.pop_back();
            --res.n;
        }
        return res;
    }

    Polynom derivative() {
        Polynom res(n -1);
        for (int i = 1; i < n; ++i) {
            res[i - 1] = data[i] * i;
        }
        return res;
    }

    Polynom integrate() {
        Polynom res(n + 1);
        for (int i = 1; i < n + 1; ++i) {
            res.data[i] = data[i - 1] / (double)i;
        }
        return res;
    }

    double operator() (double x) {
        double res = 0.0;
        double xi = 1.0;
        for (double elem : data) {
            res += elem * xi;
            xi *= x;
        }
        return res;
    }

    double integrate(double l, double r) {
        Polynom F = integrate();
        return F(r) - F(l);
    }

    friend std::ostream & operator << (std::ostream &out, const Polynom &poly) {
        bool flag = false;
        int deg = 0;
        for (double elem: poly.data) {
            if (!(std::abs(elem) < eps)) {
                if (flag && deg) {
                    out << (elem > eps ? " + " : " - ");
                }
                out << std::abs(elem);
                flag = true;
                if (deg) {
                    out << " * x";
                    if (deg > 1) {
                        out << "^" << deg;
                    }
                }
            }
            ++deg;
        }
        if (!flag) {
            out << 0;
        }
        return out;
    }
    ~Polynom() = default;
};

#endif //NM3_1_POLYNOM_H
