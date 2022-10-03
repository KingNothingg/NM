#include "matrix.cpp"

#include <algorithm>
#include <cmath>
#include <utility>

template <class T>
class LU {
private:
    const T EPS = 1e-6;

    Matrix<T> L, U;
    T determinant;
    std::vector<std::pair<int,int>> swaps;

    void decompose() {
        int n = U.Size();
        for (int i = 0; i < n; ++i) {
            int maxEl = i;
            for (int j = i + 1; j < n; ++j) {
                if (abs(U[j][i]) > abs(U[maxEl][i])) {
                    maxEl = j;
                }
            }
            if (maxEl != i) {
                std::pair<int,int> swap = std::make_pair(i, maxEl);
                swaps.push_back(swap);
                U.swapRows(i, maxEl);
                L.swapRows(i, maxEl);
                L.swapColumns(i, maxEl);
            }
            for (int j = i + 1; j < n; ++j) {
                if (abs(U[i][i]) < EPS) {
                    continue;
                }
                T m = U[j][i]/U[i][i];
                L[j][i] = m;
                for (int k = 0; k < n; ++k) {
                    U[j][k] -= m * U[i][k];
                }
            }
        }
        if (swaps.size() % 2 == 1) {
            determinant = -1;
        } else determinant = 1;
        for (int i = 0; i < n; ++i) {
            determinant *= U[i][i];
        }
    }
    void Swap(std::vector<T> &a) {
        for (auto &i : swaps) {
            std::swap(a[i.first], a[i.second]);
        }
    }
public:
    LU(const Matrix<T> &m) : L(m.Size(), true), U(m){
        decompose();
    }
    friend std::ostream & operator << (std::ostream &out, const LU<T> lu) {
        out << "Lower matrix:\n" << lu.L << "Upper matrix:\n" << lu.U;
        return out;
    }
    T Determinant() {
        return determinant;
    }
    std::vector<T> solve(std::vector<T> b){
        int n = b.size();
        Swap(b);
        std::vector<T> z(n);
        for (int i = 0; i < n; ++i) { //Lz = b
            T summ = b[i];
            for (int j = 0; j < i; ++j){
                summ -= z[j] * L[i][j];
            }
            z[i] = summ;
        }
        std::vector<T> x(n);
        for (int i = n - 1; i >= 0; --i) { // Ux = z
            if (abs(U[i][i]) < EPS) {
                continue;
            }
            T summ = z[i];
            for (int j = n - 1; j > i; --j) {
                summ -= x[j] * U[i][j];
            }
            x[i] = summ/U[i][i];
        }
        return x;
    }
    ~LU() = default;
};
