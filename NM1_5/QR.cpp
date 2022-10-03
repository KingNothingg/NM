#include "matrix.cpp"
#include <complex>
#include <cmath>

class QR {
private:
    static constexpr double INF = 1e18;
    static constexpr std::complex<double> COMP_INF = std::complex<double>(INF, INF);

    int n;
    Matrix<double> a;
    double eps;
    std::vector<std::complex<double>> eigen;

    // V^T * V
    double vtv(const std::vector<double> &vec) {
        double res = 0;
        for (auto elem: vec) {
            res += elem*elem;
        }
        return res;
    }

    double norm2(const std::vector<double> &vec) {
        return std::sqrt(vtv(vec));
    }

    Matrix<double> vvt(const std::vector<double> &vec) {
        int size = vec.size();
        Matrix<double> res(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                res[i][j] = vec[i] * vec[j];
            }
        }
        return res;
    }

    double sign(double x) {
        if (x < eps) {
            return -1.0;
        } else if (x > eps) {
            return 1.0;
        }
    }


    Matrix<double> HH(const std::vector<double> &vec, int el) {
        std::vector<double> v(vec);
        v[el] += sign(vec[el]) * norm2(vec);
        return Matrix<double>(n, true) - (2.0 / vtv(v)) * vvt(v);  //E - (2/vtv)*vvt
    }

    // (ajj - l)(aj1j1 - l) = ajj1 * aj1j
    // ajj * aj1j1 - ajj * l - aj1j1 * l - ajj1 * aj1j + l*l = 0
    // l^2 - l * (-ajj - aj1j1) + ajj1 * aj1j - ajj1 * aj1j = 0
    std::pair<std::complex<double>, std::complex<double>> eq_solver(double ajj, double aj1j1, double ajj1, double aj1j) {
        double a = 1.0;
        double b = - (ajj + aj1j1);
        double c = ajj * aj1j1 - aj1j * ajj1;
        double dd = b * b - 4 * a * c;
        if (dd > eps) {
            std::complex<double> bad(NAN, NAN);
            return std::make_pair(bad, bad);
        }
        std::complex<double> d(0.0, std::sqrt(-dd));
        std::complex<double> x1 = (-b + d) / (2.0 * a);
        std::complex<double> x2 = (-b - d) / (2.0 * a);
        return std::make_pair(x1,x2);
    }

    void calcEigen() {
        for (int i = 0; i < n; ++i) {
            if (i < n - 1 && !(std::abs(a[i+1][i]) < eps)) { //if subdiagonal are not small
                auto [l1, l2] = eq_solver(a[i][i], a[i+1][i+1], a[i][i+1], a[i+1][i]);
                if (std::isnan(l1.real())) {
                    ++i;
                    continue;
                }
                eigen[i] = l1;
                eigen[++i] = l2;
            } else {
                eigen[i] = a[i][i];
            }
        }
    }

    bool checkDiag(){
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = i + 2; j < n; ++j) {
                sum += a[j][i] * a[j][i];
            }
            double norm = std::sqrt(sum);
            if (!(norm <eps)) {
                return false;
            }
        }
        return true;
    }

    bool checkEps() {
        if (!checkDiag()) {
            return false;
        }
        std::vector<std::complex<double>> prev(eigen);
        calcEigen();
        for (int i = 0; i < n; ++i) {
            double delta = std::norm(eigen[i] - prev[i]);
            if (delta > eps) {
                return false;
            }
        }
        return true;
    }

    void build() {
        iter_count = 0;
        while (!checkEps()) {
            ++iter_count;
            Matrix<double> q(n, true);
            Matrix<double> r(a);
            for (int i = 0; i < n - 1; ++i){
                std::vector<double> b(n);
                for (int j = i; j < n;  ++j) {
                    b[j] = r[j][i];
                }
                Matrix<double> h = HH(b,i);
                q = q * h; // Q_k = H1*H2*...*H_k
                r = h * r;
            }
            a = r * q;
        }
    }

public:
    int iter_count;

    QR(const Matrix<double> &_a, double _eps) : n(_a.Size()), a(_a), eps(_eps), eigen(n, COMP_INF) {
        build();
    }
    std::vector<std::complex<double>> getEigen() {
        calcEigen();
        return eigen;
    }

    ~QR() = default;
};

