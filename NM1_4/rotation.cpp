//только для симметрических матриц A^T = A
#include <cmath>
#include "matrix.cpp"

class Rotation {
private:
    int n;
    Matrix<double> a;
    double eps;
    Matrix<double> v;

    static double EndCondition(const Matrix<double> &m) {
        int n = m.Size();
        double result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                result += m[i][j] * m[i][j];            // сумма квадратов внедиагональных элементов
            }
        }
        return std::sqrt(result);
    }

    double CalculatePhi(int i, int j) {
        if (std::abs(a[i][i] - a[j][j]) < 1e-9) {
            return std::atan(1.0); //pi/4
        } else {
            return 0.5 * std::atan(2*a[i][j]/(a[i][i] - a[j][j]));
        }
    }

    Matrix<double> CreateRotationMatrix(int i, int j, double phi) {
        Matrix<double> u(n, true);
        u[i][i] = std::cos(phi);
        u[i][j] = -std::sin(phi);
        u[j][i] = std::sin(phi);
        u[j][j] = std::cos(phi);
        return u;
    }

    void Build() {
        count = 0;
        while(EndCondition(a) > eps) {
            ++count;
            int max_i = 0, max_j = 1;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == j) {
                        continue;
                    }
                    if (std::abs(a[i][j]) > std::abs(a[max_i][max_j])) {
                        max_i = i;
                        max_j = j;
                    }
                }
            }
            double phi = CalculatePhi(max_i, max_j);
            Matrix<double> u = CreateRotationMatrix(max_i, max_j, phi);
            v = v * u;
            a = u.Transponse() * a * u;
        }
    }

public:
    int count;

    Rotation(const Matrix<double> &_a, double _eps): n(_a.Size()), a(_a), eps(_eps), v(n, true){
        Build();
    }
    Matrix<double> getEigenVectors() {
        return v;
    }
    std::vector<double> getEigenValues() {
        std::vector<double> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = a[i][i];
        }
        return result;
    }

    ~Rotation() = default;
};