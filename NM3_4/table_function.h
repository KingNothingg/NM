#ifndef NM3_4_TABLE_FUNCTION_H
#define NM3_4_TABLE_FUNCTION_H

#include <vector>
#include <cmath>

const double EPS = 1e-9;

bool leq(double a, double b) {
    return (a < b) or (std::abs(b - a) < EPS);
}

class table_function {
    int n;
    std::vector<double> x, y;
public:
    table_function(const std::vector<double> &_x, const std::vector<double> &_y) {
        x = _x;
        y = _y;
        n = x.size();
    }

    double derivative1(double x0) {
        for (int i = 0; i < n - 1; ++i) {
            if (x[i] <  x0 && leq(x0, x[i+1])) { //Первая степень интерполяционного многочлена
                double res = (y[i + 1] - y[i - 1])/(x[i + 1] - x[i - 1]);
                return res;
            }
        }
        return NAN;
    }

    double derivative2(double x0) {
        for (int i = 0; i < n - 1; ++i) {
            if (x[i] < x0 && leq(x0, x[i+1])) {
                double res = (y[i - 1] - 2*y[i] + y[i + 1])/pow((x[i + 1] - x[i]), 2);
                return res;
            }
        }
        return NAN;
    }
};

#endif //NM3_4_TABLE_FUNCTION_H
