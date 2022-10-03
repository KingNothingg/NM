#include "tridiag.cpp"

int main() {
    std::cout.precision(6);
    std::cout << std::fixed;
    int n;
    std::cin >> n;
    Tridiag<double> A(n);
    std::cin >> A;
    std::vector<double> b(n);
    for (int i = 0; i < n;++i) {
        std::cin >> b[i];
    }
    std::vector<double> x = A.Solve(b);
    std::cout << "Решение системы: \n";
    for (int i = 0; i < n; ++i) {
        std::cout << "x" << i + 1 << " = " << x[i] << '\n';
    }
}
