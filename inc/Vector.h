#pragma once

#include <iostream>

/**
 * @brief Dynamic any type Vector class.
 */
template <typename Tf>
class Vector{
private:
    /**
     * @brief Values of sent type.
    * @return Pointer to table of variables.
    */
    Tf *value;

    /**
     * @brief Size of Vector.
    */
    std::size_t dim;

public:
    /**
     * @brief Construct a new empty Vector.
    */
    Vector();

    /**
     * @brief Construct a new Vector object.
    * @param v Vector to copy.
    */
    Vector(const Vector<Tf> &v);

    /**
     * @brief Construct a new Vector with parameters.
     * Dimention depends how many arguments put.
    */
    template <typename... T>
    Vector(const Tf &first, const T... args);

    /**
     * @brief Construct a new Vector object make 1x1 Vector
     * @param first value inside the Vector
     */
    Vector(const Tf &first);
    
    /**
     * @brief Destroy the Vector object
    */
    ~Vector();

    /**
     * @brief Acces to dimension of Vector.
     * @return unsigned int dim of Vector.
    */
    std::size_t Dim() const;

    /**
     * @brief Count length of Vector
    * @return Tf length of vector
    */
    Tf Length() const;

    /**
     * @brief Put value on Vector and increase dimention
     * @param value 
     */
    void Put(const Tf &value);

    /**
     * @brief Takes last element and pop;
     * @return Taken value.
     */
    Tf Pop();

    /**
     * @brief Remove value at index.
     * @param index of removed value.
     * @return double removed value.
     */
    Tf Remove(const std::size_t index);

    /**
     * @brief Acces to variables vector.
    */
    Tf operator[](const std::size_t &i) const;

    /**
     * @brief Acces to variables vector.
    */
    Tf &operator[](const std::size_t &i);

    /**
     * @brief Compare two Vectors. Dimention and values
     * @param u compare Vector
     * @return True when dimention and values are the same,
                False when  not.
    */
    bool operator==(const Vector<Tf> &u) const;

    /**
     * @brief Compare two Vectors. Dimention and values.
     * @param u Compare Vector.
     * @return False when dimention and values are the same,
                true when  not.
    */
    bool operator!=(const Vector<Tf> &v) const;

    /**
     * @brief Check if Vector is empty
    * @return true when is empty,
                false when is not.
    */
    bool operator!() const;

    /**
     * @brief Assignment operator
    */
    Vector &operator=(const Vector &v);

    /**
     * @brief Additaion operator
    */
    Vector operator+(const Vector &v) const;

    /**
     * @brief Substraction operator
    */
    Vector operator-(const Vector &v) const;

    /**
     * @brief Multiplication by number
    */
    Vector operator*(const Tf &k);

    /**
     * @brief Dot product 
    */
    Tf operator*(const Vector &v);

    /**
     * @brief Division by number
    */
    Vector operator/(const Tf &k);
};

/**
 * @brief Output stream operator 
 * @return std::ostream& cout [x, y, ...]
 */
template <typename Tf>
std::ostream &operator<<(std::ostream &cout, const Vector<Tf> &v);

/**
 * @brief Input stream operator
 * @return std::istream& cin with [x1, x2, x3...]
 */
template <typename Tf>
std::istream &operator>>(std::istream &cin, Vector<Tf> &v);

/**
 * @brief include definitions.
*/
#include "Vector.cpp"