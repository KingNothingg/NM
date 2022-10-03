#include <cmath>
#include "interpolation.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        y[i] = asin(x[i]) + x[i];
    }
    double point;
    cin >> point;
    Lagrange l(x, y);
    Polynom lagrange = l();
    cout << "Интерполяционный многочлен Лагранжа: " << lagrange << '\n';
    cout << "Погрешность в точке Х*: " << abs(lagrange(point) - asin(point) - point) << '\n';

    Newton ne(x,y);
    Polynom newton = ne();
    cout << "Интерполяционный многочлен Ньютона: " << newton << '\n';
    cout << "Погрешность в точке Х*: " << abs(newton(point) - asin(point) - point) << '\n';
}
