#include <iostream>
#include "table_function.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    std::vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> y[i];
    }
    double x0;
    cin >> x0;

    cout.precision(4);
    cout << fixed;
    table_function f(x,y);
    cout << "Первая производная функции в точке x0 = " << x0 << ", f'(x0) = " << f.derivative1(x0) << endl;
    cout << "Вторая производная функции в точке x0 = " << x0 << ", f''(x0) = " << f.derivative2(x0) << endl;
}
