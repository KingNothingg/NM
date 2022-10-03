#include "iter.cpp"

int main() {
    std::cout.precision(6);
    std::cout << std::fixed;
    int n;
    double eps;
    std::cin >> n >> eps;
    matrix_t<double> a(n);
    std::cin >> a;
    iter_solver iter(a, eps);
    std::vector<double> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    std::vector<double> x1 = iter.solve_simple(b);
    std::cout << "Метод простых итераций, решение системы:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "x" << i + 1 << " = " << x1[i] << '\n';
    }
    std::cout << "Количество итераций: " << iter.iter_count << '\n';

    std::vector<double> x2 = iter.solve_zeidel(b);
    std::cout << "Метод Зейделя, решение системы:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "x" << i + 1 << " = " << x2[i] << '\n';
    }
    std::cout << "Количество итераций: " << iter.iter_count << '\n';
}
