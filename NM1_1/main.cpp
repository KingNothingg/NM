#include <iostream>
#include "lu.cpp"

Matrix<double> Inverse(LU<double> A, int n) {
    Matrix<double> result(n);
    for (int i = 0; i < n; ++i) {
        std::vector<double> b(n);
        b[i] = 1;
        std::vector<double> x = A.solve(b);
        for (int j = 0; j < n; ++j) {
            result[j][i] = x[j];
        }
    }
    return result;
}

int main() {
    std::cout.precision(6);
    std::cout << std::fixed;
    int n;
    std::cin >> n;
    Matrix<double> a(n);
    std::cin >> a;
    LU<double> A(a);
    //std::cout << A << "\n";
    std::vector<double> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    std::vector<double> x = A.solve(b);
    std::cout << "Решение системы: \n";
    for (int i = 0; i < n; ++i) {
        std::cout << "x" << i+1 << "=" << x[i] << '\n';
    }
    std::cout << "Определитель: " << A.Determinant() << '\n';
    std::cout << "Обратная матрица: \n";
    std::cout << Inverse(A, n) << '\n';
}
