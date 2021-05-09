#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include "config.hpp"
#include "Object.hpp"
#include "GnuPlotApi.hpp"
#include <vector>


class Scene: public PzG::LaczeDoGNUPlota{
    std::vector<Object*> objects;

    public:
        Scene();

        ~Scene();

        void AddObject(Object &obj);

        void Update();

        void Start();

        Object &operator[](const std::size_t &i);
};
#endif // __SCENE_HPP__