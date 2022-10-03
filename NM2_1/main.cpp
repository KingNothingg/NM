#include "eqSolver.cpp"
#include <iostream>

using namespace std;

int main() {
    cout.precision(9);
    cout << fixed;
    double l, r, eps;
    cin >> l >> r >> eps;
    double root;
    root = iterations(l, r, eps);
    cout << "Метод простой итерации. Количество итераций: " << iterCount << "\nx_0 = " << root << '\n';
    root = newton(l, r, eps);
    cout << "Метод Ньютона. Количество итераций: " << iterCount << "\nx_0 = " << root << '\n';
}
