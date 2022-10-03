#include <iostream>
#include "spline.h"

using namespace std;

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
    double point;
    cin >> point;

    cout. precision(5);
    cout << fixed;
    Spline spline(x, y);
    cout << "Сплайн: " << spline  << '\n';
    cout << "Значение в точке X*: " << spline(point) << "\n";
}
