#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include <iostream>
#include <string>
#include <vector>
/**
 * @brief Collects position, angles and scale of whole object. 
 */
struct Transform{
    public:
        Vector3 position;

        Vector3 angles;

        Vector3 scale;

        Transform(){
            position    = Vector3();
            angles      = Vector3();
            scale       = Vector3({1, 1, 1});
        }
};


/**
 * @brief Object Class, base class for printed objects on screen
 */
class Object{
    private:
        /**
         * @brief Name of Object
         */
        std::string name;

        /**
         * @brief List of points of Object
         */
        std::vector<Vector3> points;
   
    public:
        /**
         * @brief Construct a new Object object
         * @param name of Object
         * @param pointNumber how many points is in the reading file
         */
        Object(const std::string name, const std::size_t &pointNumber);

        virtual ~Object();
        
        /**
         * @brief Informations about position of center point, angles and scale
         */
        Transform transform;

        /**
         * @brief Acces function for name of Object
         * @return std::string name of Object
         */
        std::string Name() const { return this->name; }

        /**
         * @brief Counts number of points
         * @return std::size_t quantity of points
         */
        std::size_t CountPoints() const {return this->points.size();}

        /**
         * @brief Acces function for reading every points
         * @param index of point in \a points
         * @return Vector3 point
         */
        Vector3 operator[](const std::size_t &index) const;

        /**
         * @brief Acces function for writing every points
         * @param index of point in \a points
         * @return Vector3 point
         */
        Vector3 &operator[](const std::size_t &index);

        /**
         * @brief Save points into file name
         */
        void Save();

        /**
         * @brief Translates every point from \a points and \a transform of Object
         * @param v translate Vector3
         */
        virtual void Translate(const Vector3 &v);

        
        /**
         * @brief Rotates every point from \a points and \a transform of Object
         * @param angle angle of rotation
         * @param times how many rotate Object
         * @param v Vector3 of axis rotation
         */
        virtual void Rotate(const double &angle, const std::size_t &times, const Vector3 &v);
};


/**
 * @brief Writing all \a points to \a Object 
 * @param strm input stream
 * @param object written \a Object
 * @return std::istream& 
 */
std::istream &operator>>(std::istream &strm, Object &object);


/**
 * @brief Printing all \a points from \a Object 
 * @param strm output stream
 * @param object printed \a Object
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &strm, const Object &object);

#endif // __OBJECT_HPP__