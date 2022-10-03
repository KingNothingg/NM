#include "rotation.cpp"

int main() {
    std::cout.precision(6);
    std::cout << std::fixed;
    int n;
    double eps;
    std::cin >> n >> eps;
    Matrix<double> a(n);
    std::cin >> a;
    Rotation rot(a, eps);
    std::vector<double> lambda = rot.getEigenValues();
    std::cout << "Собственные значения:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "l" << i + 1 << " = " << lambda[i] << '\n';
    }
    std::cout << "Собственные векторы: \n";
    Matrix<double> s = rot.getEigenVectors();
    std::cout << s;
    std::cout << "Количество итераций: " << rot.count << '\n';
}
