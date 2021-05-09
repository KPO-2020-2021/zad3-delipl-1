#include "Scene.hpp"

Scene::Scene(){
    this->UsunWszystkieNazwyPlikow();
    this->_Xmax =  10 * WINDOW_SCALE;
    this->_Xmin = -10 * WINDOW_SCALE;
    this->_Ymax =  10  * WINDOW_SCALE;
    this->_Ymin = -10  * WINDOW_SCALE;
    this->_Zmax =  10  * WINDOW_SCALE;
    this->_Zmin =  0 * WINDOW_SCALE;
    this->ZmienTrybRys(PzG::TR_3D);
    this->Inicjalizuj();

    this->objects = std::vector<Object*>();
}

Scene::~Scene(){
    system("killall gnuplot");
}

void Scene::AddObject(Object &obj){
    this->DodajNazwePliku(std::string(TMP_TEST_FOLDER + obj.Name()).c_str());
    this->objects.push_back(&obj);
}

Object &Scene::operator[](const std::size_t &i){
    if(i >= this->objects.size())
        throw std::overflow_error("There is no more objects");
    return *(this->objects[i]);
}
        
void Scene::Update(){
    for(auto obj : this->objects){
        obj->Save();
    }
    this->Rysuj();
}

void Scene::Start(){

}