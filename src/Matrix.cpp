#include <cmath>
#include "Matrix.h"

/* -------------------------------------------------------------------------- */
/*                                CONSTRUCTORS                                */
/* -------------------------------------------------------------------------- */
template <typename Tf>
Matrix<Tf>::Matrix() {
    this->m = 0;
    this->n = 0;
}

template <typename Tf>
template <typename... Tv>
Matrix<Tf>::Matrix(const Vector<Tf> &first, const Tv... args) {
    this->n = sizeof...(args) + 1;
    this->m = first.Dim();
    Vector<Tf> tempTab[sizeof...(args)] = {args...};
    for (int i = 0; i < this->n - 1; i++) {
        if (first.Dim() != tempTab[i].Dim())
            throw std::out_of_range("Vector in Matrix doesn't have same type");
    }
    this->vector = new Vector(first, args...);
}

template <typename Tf>
Matrix<Tf>::Matrix(const Vector<Vector<Tf>> &tab) {
    this->n = tab.Dim();
    this->m = tab[0].Dim();
    this->vector = new Vector(tab);
}

template <class Tf>
Matrix<Tf>::~Matrix() {
    delete this->vector;
}

/* -------------------------------------------------------------------------- */
/*                                   METHODS                                  */
/* -------------------------------------------------------------------------- */
template <class Tf>
Vector<Tf> Matrix<Tf>::Det() const {
    if (this->n == 2 && this->m == 3) {
        Matrix M(Vector(1, 1, 1), (*this)[0], (*this)[1]);
        Tf a(M(1, 1) * M(2, 2) - M(1, 2) * M(2, 1));
        Tf b(M(1, 2) * M(2, 0) - M(1, 0) * M(2, 2));
        Tf c(M(1, 0) * M(2, 1) - M(1, 1) * M(2, 0));
        return Vector(a, b, c);
    } else {
        throw std::out_of_range("Matrix cannnot define determinant");
    }
}

/* -------------------------------------------------------------------------- */
/*                                  OPERATORS                                 */
/* -------------------------------------------------------------------------- */
template <class Tf>
Tf Matrix<Tf>::operator()(const std::size_t &n, const std::size_t &m) const {
    return ((*this->vector)[n])[m];
}

template <class Tf>
Vector<Tf> &Matrix<Tf>::operator[](const std::size_t &index) const {
    return (*this->vector)[index];
}

template <class Tf>
Vector<Tf> Matrix<Tf>::operator*(const Vector<Tf> &v) const {
    Vector<Tf> u;
    Tf x;
    for (int i = 0; i < this->m; i++) {
        x = (*this->vector)[i] * v;
        u.Put(x);
    }
    return u;
}

template <typename Tf>
Vector<Tf> operator&(const Vector<Tf> &v, const Vector<Tf> &u) const{
    if (v.Dim() != u.Dim() || v.Dim() != 3)
        throw std::logic_error("Cross product doesn't defined");
    Vector tempV(v);
    Vector tempU(u);

    Matrix M(tempV, tempU);
    return M.Det();
}

template <typename Tf>
std::ostream &operator<<(std::ostream &cout, const Matrix &M){
    for (int i = 0; i < M.N(); i++){
        cout << "| ";
        for (int j = 0; j < M.M(); j++) {
            cout << M(i, j) << " ";
        }
        cout << "|" << std::endl;
    }
    return cout;
}