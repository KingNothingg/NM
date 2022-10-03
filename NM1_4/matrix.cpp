#include <vector>
#include <iostream>
template <class T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    int size;
public:
    Matrix(int n, bool identity = false) : size(n) {
        data.resize(size, std::vector<T>(size));
        if (identity) {
            for (int i = 0; i < size; ++i) {
                data[i][i] = 1;
            }
        }
    }
    int Size() const {
        return size;
    }
    void swapRows(int i, int j) {
        if (i == j) return;
        for (int l = 0; l < size; ++l) {
            std::swap(data[i][l], data[j][l]);
        }
    }
    void swapColumns(int i, int j) {
        if (i == j) return;
        for (int l = 0; l < size; ++l) {
            std::swap(data[l][i], data[l][j]);
        }
    }
    Matrix<T> Transponse() {
        Matrix<T> result(*this);
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                std::swap(result[i][j], result[j][i]);
            }
        }
        return result;
    }
    friend std::vector<T> operator *(const std::vector<std::vector<T>> &a, const std::vector<T> &b) {
        std::vector<T> res(a.size());
        for (int i = 0; i < res.size(); ++i) {
            for (int j = 0; j < res.size(); ++j) {
                res[i] += a[i][j] * b[j];
            }
        }
        return res;
    }
    friend std::vector<T> operator *(const Matrix<T> &a, const std::vector<T> &b) {
        std::vector<T> res(a.Size());
        for (int i = 0; i < res.size(); ++i) {
            for (int j = 0; j < res.size(); ++j) {
                res[i] += a[i][j] * b[j];
            }
        }
        return res;
    }

    friend Matrix<T> operator *(const Matrix<T> &a, const Matrix<T> &b) {
        Matrix<T> res(a.Size());
        for (int i = 0; i < res.Size(); ++i) {
            for (int j = 0; j < res.Size(); ++j) {
                for (int k = 0; k < res.Size(); ++k) {
                    res[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return res;
    }
    std::vector<T> & operator [] (int i) {
        return data[i];
    }

    const std::vector<T> & operator [] (int i) const {
        return data[i];
    }
    friend std::ostream & operator << (std::ostream &out, const Matrix<T> &a) {
        for (int i = 0; i < a.Size(); ++i) {
            for (int j = 0; j < a.Size(); ++j) {
                out << a[i][j] << ' ';
            }
            out << "\n";
        }
        return out;
    }
    friend std::istream & operator >> (std::istream &in, Matrix<T> &a) {
        for (int i = 0; i < a.Size(); ++i) {
            for (int j = 0; j < a.Size(); ++j) {
                in >> a[i][j];
            }
        }
        return in;
    }
    ~Matrix() = default;
};
template <class T>
std::vector<T> operator +(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> res(a.size());
    for (int i = 0; i < res.size(); ++i) {
        res[i] = a[i] + b[i];
    }
    return res;
}
template <class T>
std::vector<T> operator -(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> res(a.size());
    for (int i = 0; i < res.size(); ++i) {
        res[i] = a[i] - b[i];
    }
    return res;
}