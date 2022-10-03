#include <iostream>
#include "solver.h"

using namespace std;

int main() {
    cout.precision(6);
    cout << fixed;
    double l1, r1, l2, r2, eps;
    cin >> l1 >> r1 >> l2 >> r2 >> eps;
    auto [x0, y0] = iter_solve(l1, r1, l2, r2, eps);
    cout << "Решение методом простых итераций: ";
    cout << x0 << " " << y0 <<'\n';
    cout << "Количество итераций: " << iter_count << '\n';
    cout << "Решение методом Ньютона: ";
    auto [x0_n, y0_n] = newton_solve(r1, r2, eps);
    cout << x0_n << " " << y0_n << '\n';
    cout << "Количество итераций: " << iter_count << '\n';
}
