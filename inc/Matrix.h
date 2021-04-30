#ifndef MATRIX_H
#define MATRIX_H
#include "Vector.h"

/**
 * @brief Matematical dynamic any type Matrix built with table of Vectors which are built with data type.
 * @tparam Tf first row as Vector.
 * @tparam Tv pack of rows as Vectors.
 */
template <typename Tf>
class Matrix {
    /**
     * @brief Rows of Matrix.
     */
    std::size_t n;

    /**
     * @brief Columns of Matrix;
     */
    std::size_t m;

    /**
     * @brief Table of rows in Matrix. Vector of Vectors.
     */
    Vector<Vector<Tf>> *vector;

public:
    /**
     * @brief Construct a new Matrix object
     */
    Matrix();

    /**
     * @brief Construct a new Matrix object.
     * @param first Vectors as a rows in the Matrix;
     */
    template < class... Tv>
    Matrix(const Vector<Tf> &first, const Tv... args);

    /**
     * @brief Construct a new Matrix object from Vector<Vector<Tf>>
     * @param tab data to copy into Matrix
     */
    Matrix(const Vector<Vector<Tf>> &tab);

    /**
     * @brief Construct a new Matrix object
     * @param M Matrix to copy
     */
    Matrix(const Matrix &M); //TODO

    /**
     * @brief Destroy the Matrix object
     */
    ~Matrix();

    /**
     * @brief Determinate for Cross product.
     * @return Vector<Tf> Cross Product.
     */
    Vector<Tf> CrossPrepare() const;

    /**
     * @brief Determinate of square Matrix
     * @param sum previous sum.
     * @return Tf determinate.
     */
    Tf Det() const;

    /**
     * @brief Flip void creating new Matrix which has columns changed to rows
     * @return Matrix channged colums with rows
     */
    Matrix Flip() const;

    /**
     * @brief Acces to N dimention rows of Matrix.
     * @return std::size_t private n value
     */
    std::size_t N() const { return this->n; };

    /**
     * @brief Acces to M dimention columns of Matrix.
     * @return std::size_t private m value
     */
    std::size_t M() const { return this->m; };

    /**
     * @brief Operator [] acces to read to row.
     * @param index of row.
     * @return Vector row in index;
     */
    Vector<Tf> operator[](const std::size_t &index) const;

     /**
     * @brief Operator [] acces ro read and write to row.
     * @param index of row.
     * @return Vector row in index;
     */
    Vector<Tf> &operator[](const std::size_t &index); 

    /**
     * @brief Multiplar operator Matrix by Vector.
     * @param v Vector.
     * @return Vector<Tf> result. 
     */
    Vector<Tf> operator*(const Vector<Tf> &v) const;

     /**
     * @brief Multiplar operator Matrix by Matrux.
     * @param M matrix.
     * @return Matrix result. 
     */
    Matrix operator*(const Matrix<Tf> &M) const;
};

/**
 * @brief Cross product.
 * @tparam Tf type of values.
 * @param v First Vector.
 * @param u Second Vector.
 * @return Vector<Tf> result of Cross product.
 */
template <typename Tf>
Vector<Tf> operator&(const Vector<Tf> &v, const Vector<Tf> &u);

/**
 * @brief Input stream operator
 * @return std::istream& cin with 
 */
template <typename Tf>
std::ostream &operator<<(std::ostream &cout, const Matrix<Tf> &M);

// template <typename Tf>
// std::istream &operator>>(std::istream &cin, Matrix &M);
#include "Matrix.cpp"
#endif