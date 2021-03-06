#include <cmath>
#include <iomanip>
#include "Matrix.h"

/* -------------------------------------------------------------------------- */
/*                                CONSTRUCTORS                                */
/* -------------------------------------------------------------------------- */
template <typename Tf>
Matrix<Tf>::Matrix() {
    this->m = 0;
    this->n = 0;
    this->vector = nullptr;
}

template <typename Tf>
template <typename... Tv>
Matrix<Tf>::Matrix(const Vector<Tf> &first, const Tv... args) {
    this->n = sizeof...(args) + 1;
    this->m = first.Dim();
    Vector<Tf> tempTab[sizeof...(args)] = {args...};
    for (std::size_t i = 0; i < this->n - 1; ++i) {
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
Vector<Tf> Matrix<Tf>::CrossPrepare() const {
    if (this->n == 2 && this->m == 3) {
        Matrix M(Vector(1, 1, 1), (*this)[0], (*this)[1]);
        Tf a(M[1][1] * M[2][2] - M[1][2] * M[2][1]);
        Tf b(M[1][2] * M[2][0] - M[1][0] * M[2][2]);
        Tf c(M[1][0] * M[2][1] - M[1][1] * M[2][0]);
        return Vector(a, b, c);
    } else {
        throw std::out_of_range("Matrix cannnot define determinant");
    }
}
template <class Tf>
Tf Matrix<Tf>::Det() const{
    Tf det = Tf(1);
    Matrix M((*this->vector));
    for(std::size_t i = 0; i < this->n; ++i){           // po wierszach
        for(std::size_t j = i; j < this->m; ++j){
            if(M[j][i] != 0){
                Tf x = M[j][i];
                // dzielenie wiersza
                M[i] = M[i]/x;
                det = det * x;

                det = (i-j % 2 == 0)? det: Tf(-1) * det; // zamiana wierszy zmienia znak w zale??no??ci od parzysto??ci
                Vector buff(M[i]);
                M[i] = M[j];
                M[j] = buff;
                // ni??sze wiersze odj??te ??eby by??o 0
                for(std::size_t k = j+1; k < this->n; ++k){
                    Tf y = M[k][j];
                    M[k] = M[k] - M[j] * y; 
                }
            }
        }
    }
    return det;
}
template <class Tf>
Matrix<Tf> Matrix<Tf>::Flip() const{
    Vector<Vector<Tf>> Mat;
    for(std::size_t j = 0; j < this->M(); j++){
        Vector<Tf> column;
        for(std::size_t i = 0; i < this->N(); i++)
            column.Put((*this)[i][j]);
        Mat.Put(column);
    }
    return Matrix(Mat);
}
/* -------------------------------------------------------------------------- */
/*                                  OPERATORS                                 */
/* -------------------------------------------------------------------------- */
template <class Tf>
Vector<Tf> Matrix<Tf>::operator[](const std::size_t &index) const {
    return (*this->vector)[index];
}

template <class Tf>
Vector<Tf> &Matrix<Tf>::operator[](const std::size_t &index){
    return (*this->vector)[index];
}

template <class Tf>
Vector<Tf> Matrix<Tf>::operator*(const Vector<Tf> &v) const {
    Vector u(v);
    for (std::size_t i = 0; i < this->m; ++i) {
        u[i] = (*this)[i] * v;
    }
    return u;
}
template <class Tf>
Matrix<Tf> Matrix<Tf>::operator*(const Matrix<Tf> &M) const{
    if(this->N() != M.M())
        throw std::logic_error("Can't multiplar this");
    Vector<Vector<Tf>> toMatrix;
    Matrix flippedMatrix = M.Flip();
    for(std::size_t i = 0; i < this->N(); ++i){
        toMatrix.Put((*this)[i] * flippedMatrix[i]);
    }
    return Matrix(toMatrix);
}

template <typename Tf>
Vector<Tf> operator&(const Vector<Tf> &v, const Vector<Tf> &u){
    if (v.Dim() != u.Dim() || v.Dim() != 3)
        throw std::logic_error("Cross product doesn't defined");
    Vector tempV(v);
    Vector tempU(u);

    Matrix M(tempV, tempU);
    return M.CrossPrepare();
}

template <typename Tf>
std::ostream &operator<<(std::ostream &cout, const Matrix<Tf> &M){
    for (std::size_t i = 0; i < M.N(); ++i){
        cout << "| ";
        for (std::size_t j = 0; j < M.M(); j++) {
            cout << std::setw(16) << std::fixed << std::setprecision(10) << M[i][j] << 0;
        }
        cout << "|" << std::endl;
    }
    return cout;
}