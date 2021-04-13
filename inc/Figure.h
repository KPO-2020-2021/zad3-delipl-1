#pragma once

#include "Vector.h"
#include "Matrix.h"

/**
 * @brief Geomethric Figure with endless points and name.
 * @tparam Tf type of typespace.
 */
template <typename Tf>
class Figure {
   protected:
    /**
     * @brief List of Points in Figure
     */
    Matrix<Tf> *points;

    /**
     * @brief Name of Figure
     */
    std::string name;

   public:
    /**
     * @brief Construct a new Figure object
     * @tparam Tv Points.
     * @param name of Figure.
     * @param first Point.
     */
    template <class... Tv>
    Figure(const std::string &name, const Vector<Tf> &first, const Tv... args);

    Figure();

    /**
     * @brief Destroy the Figure object
     */
    ~Figure();

    /**
     * @brief Acces to name
     * @return std::string name of figure.
     */
    std::string Name() const { return this->name; }

    /**
     * @brief Counts how many Points in Figure are.
     * @return std::size_t quantity of Points
     */
    std::size_t CountPoints() const { return this->points->N(); };

    /**
     * @brief Rotate Figure around Vector ref.
     * @param angle to Rotate.
     * @param ref Point of Reference.
     * @return Figure rotated Figure;
     */
    void Rotate(const double &angle, const Vector<Tf> &v = Vector(Tf(), Tf()));

    /**
     * @brief Returns point.
     * @param index index of point. 
     * @return Vector<Tf> Point.
     */
    virtual Vector<Tf> operator[](const std::size_t &index) const {
        return (*this->points)[index];
    }

    /**
     * @brief 
     * @param cin 
     * @param figure 
     * @return std::istream& 
     */
    friend std::istream &operator>>(std::istream &cin, Figure &figure);

    friend std::ostream &operator<<(std::ostream &cout, const Figure &figure);
};

/**
 * @brief Rectangle Figure. It has 4 Points and constructos checking if is Rectangle
 * @tparam Tf typespace
 */
template <typename Tf>
class Rectangle : public Figure<Tf> {
   public:
    /**
     * @brief Construct a new Rectangle object
     * @param A first Point.
     * @param B second Point.
     * @param C third Point.
     * @param D forth Point.
     */
    Rectangle(const Vector<Tf> &A, const Vector<Tf> &B, const Vector<Tf> &C, const Vector<Tf> &D);

    /**
     * @brief Construct a new Rectangle object
     * @param a Length of first side
     * @param b Length of second side
     */
    Rectangle(const Tf &a, const Tf &b);

    friend std::istream &operator>>(std::istream &cin, Rectangle &figure);
};

#include "Figure.cpp"