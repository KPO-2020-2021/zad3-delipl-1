#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "GnuPlotApi.hh"
#include <fstream>

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

    /**
     * @brief Construct a new Figure object
     */
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
     * @brief Return dimention pf figure
     * @return std::size_t 
     */
    std::size_t Dimention() const { return this->points->M(); };

    /**
     * @brief Rotate Figure around Vector ref.
     * @param angle to Rotate.
     * @param ref Point of Reference.
     * @return Figure rotated Figure;
     */
    virtual void Rotate(const double &angle, const std::size_t &x = 1,const Vector<Tf> &v = Vector(Tf(), Tf()));

    /**
     * @brief Returns point to read.
     * @param index index of point. 
     * @return Vector<Tf> Point.
     */
    Vector<Tf> operator[](const std::size_t &index) const;
    /**
     * @brief Returns point to read and write.
     * @param index index of point. 
     * @return Vector<Tf> Point.
     */
    Vector<Tf> &operator[](const std::size_t &index);
};

/**
 * @brief 
 * @param cin 
 * @param figure 
 * @return std::istream& 
 */
template <typename Tf>
std::istream &operator>>(std::istream &cin, Figure<Tf> &figure);

template <typename Tf>
std::ostream &operator<<(std::ostream &cout, const Figure<Tf> &figure);

template <typename Tf>
class GnuFigure : public Figure<Tf>, public PzG::LaczeDoGNUPlota{
    private:
        std::string fileName;
        std::fstream *tmpFile;
    public:
        GnuFigure();
        template <class... Tv>
        GnuFigure(const std::string &fileName, const Vector<Tf> &first, const Tv... args);

        GnuFigure(const std::string &fileName,const std::size_t &dim);

        ~GnuFigure();

        bool Save(const std::string &fileName);

        bool Draw();

        void Rotate(const double &angle, const std::size_t &x = 1, const Vector<Tf> &v = Vector(Tf(), Tf()));

};

#include "Figure.cpp"