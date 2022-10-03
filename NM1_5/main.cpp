#include "QR.cpp"

using namespace std;

int main() {
    int n;
    double eps;
    cin >> n >> eps;
    Matrix<double> a(n);
    cin >> a;
    QR qr(a, eps);
    vector<complex<double>> lambda = qr.getEigen();
    cout << "Количество итераций: " << qr.iter_count << '\n';
    cout << "Собственные значения:\n";
    for (int i = 0; i < n; ++i) {
        cout << "l_" << i + 1 << " = " << lambda[i].real();
        if (lambda[i].imag() != 0) {
            cout << " + i * " << lambda[i].imag() << "\n";
        } else {
            cout << '\n';
        }
    }
}
