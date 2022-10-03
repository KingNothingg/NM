#include "MNK.h"

using namespace std;

double f0(double x) {
    return 1.0;
}

double f1(double x) {
    return x;
}

double f2(double x) {
    return x * x;
}

int main() {
    int n;
    cin >> n;
    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> y[i];
    }
    cout.precision(5);
    cout << fixed;
    vector<function<double(double)>> phi = {f0, f1};
    MNK mnk1(x, y, phi);
    cout << "Приближающий многочлен первой степени: " << mnk1 << '\n';
    cout << "Сумма квадратов ошибок: " << mnk1.error() << '\n';

    phi.push_back(f2);
    MNK mnk2(x, y, phi);
    cout << "Приближающий многочлен второй степени: " << mnk2 << '\n';
    cout << "Сумма квадратов ошибок: " << mnk2.error() << '\n';
}
