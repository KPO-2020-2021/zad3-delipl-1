#include <Figure.h>
#include <limits>
#include <iomanip> 
#include <unistd.h>
#define SCALE 30
/* -------------------------------------------------------------------------- */
/*                             FIGURE CONSTRUCTORS                            */
/* -------------------------------------------------------------------------- */
template <typename Tf>
template <class... Tv>
Figure<Tf>::Figure(const std::string &name, const Vector<Tf> &first, const Tv... args)
{
    this->name = name;
    this->points = new Vector(first, args...);
}
template <typename Tf>
Figure<Tf>::Figure()
{
    this->name = "";
    this->points = nullptr;
}

template <typename Tf>
Figure<Tf>::~Figure()
{
    delete this->points;
}

/* -------------------------------------------------------------------------- */
/*                               FIGURE METHODS                               */
/* -------------------------------------------------------------------------- */
template <typename Tf>
std::size_t Figure<Tf>::CountPoints() const { 
    return this->points == nullptr? 0: this->points->Dim(); 
}

template <typename Tf>
std::size_t Figure<Tf>::Dimention() const { 
    return this->points == nullptr? 0 :(*this->points)[0].Dim(); 
}

template <typename Tf>
void Figure<Tf>::Rotate(const double &angle, const std::size_t &x, const Vector<Tf> &v)
{
    Matrix<Tf> M(Vector(Tf(cos(angle)), Tf(-sin(angle))),
                 Vector(Tf(sin(angle)), Tf(cos(angle))));
    for (std::size_t j = 0; j <x; j++){
        for (std::size_t i = 0; i < this->CountPoints(); i++){
            Vector u = (*this->points)[i];
            u = u - v;
            Vector w = M * u;
            (*this->points)[i] = w + v;
        }
    }
}
template <typename Tf>
void Figure<Tf>::Translate(const Vector<Tf> &v){
    for(std::size_t i = 0; i < this->CountPoints(); i++){
        (*this->points)[i] = (*this->points)[i] + v;
    }
}
/* -------------------------------------------------------------------------- */
/*                              FIGURE OPERATORS                              */
/* -------------------------------------------------------------------------- */
// in header
// virtual Vector<Tf> Figure<Tf>::operator[](const std::size_t &index) const{
// virtual Tf Figure<Tf>::operator()(const std::size_t &n, const std::size_t &m) const{
template <typename Tf>
Vector<Tf> & Figure<Tf>::operator[](const std::size_t &index){
        return (*this->points)[index];
}
template <typename Tf>
Vector<Tf> Figure<Tf>::operator[](const std::size_t &index)const{
        return (*this->points)[index];
}
template <typename Tf>
std::ostream &operator<<(std::ostream &cout, Figure<Tf> &figure){
    for (std::size_t i = 0; i < figure.CountPoints(); i++){
        for (std::size_t j = 0; j < figure.Dimention(); j++)
            cout << std::setw(16) << std::fixed << std::setprecision(10) << figure[i][j];
        cout << std::endl;
    }
    for (std::size_t j = 0; j < figure.Dimention(); j++)
        cout << std::setw(16) << std::fixed << std::setprecision(10) << figure[0][j];
    cout << std::endl;
    return cout;
}

template <typename Tf>
std::istream &operator>>(std::istream &cin, Figure<Tf> &figure)
{
    for (std::size_t i = 0; i < figure.CountPoints(); i++)
    {
        cin >> figure[i];
        if (!cin)
            throw std::logic_error("Can't read Rectangle");
    }
    return cin;
}
/* -------------------------------------------------------------------------- */
/*                           GNUFIGURE CONSTRUCTORS                           */
/* -------------------------------------------------------------------------- */
// template <typename Tf>
// GnuFigure<Tf>::GnuFigure(){
//     this->tmpFile = nullptr;
//     this->points = nullptr;
//     this->velocity = nullptr;

//     this->dim = 0;
//     this->animateFPS = 1;
// }
template <typename Tf>
GnuFigure<Tf>::GnuFigure(const std::string &name, const std::size_t &dim){
    this->UsunOstatniaNazwe();
    this->UsunOstatniaNazwe();
    this->name = name;
    this->fileName = "../tmp/_" + name;
    this->dim = dim;
    this->animateFPS = 1;
    
    this->_Xmax =  16*SCALE;
    this->_Xmin = -16*SCALE;
    this->_Ymax =  9*SCALE;
    this->_Ymin = -9*SCALE; 

    this->Read(name);
    // Vector<Tf> T;
    // for(std::size_t i = 0; i < dim; ++i){
    //     T.Put(Tf(0));
    // }
    // this->force = new Vector(T);
    // this->velocity = new Vector(T);

    this->tmpFile = new std::ofstream;
    this->tmpFile->open(this->fileName);

    this->ZmienTrybRys(PzG::TR_2D);
    this->DodajNazwePliku(this->fileName.c_str(), PzG::RR_Ciagly, 2);
    this->DodajNazwePliku(this->fileName.c_str(), PzG::RR_Punktowy, 2);
}

template <typename Tf>
GnuFigure<Tf>::~GnuFigure(){
    this->tmpFile->close();
    delete this->tmpFile;
}

/* -------------------------------------------------------------------------- */
/*                              GNUFIGURE METHODS                             */
/* -------------------------------------------------------------------------- */
template <typename Tf>
bool GnuFigure<Tf>::Save(const std::string &name){
    std::ofstream file;
    file.open("../datasets/"+name);
    file << *this;
    file.close();
    return true;
}

template <typename Tf>
bool GnuFigure<Tf>::Read(const std::string &name){
    std::ifstream file;
    if(this->points != nullptr)
        delete this->points;

    file.open("../datasets/"+name);
    
    if(!file.good())
        throw std::logic_error("File not found");

    Vector<Tf> T;
    for(std::size_t i = 0; i < this->dim; ++i)
        T.Put(Tf());
    
    Vector<Vector<Tf>> Y;
    std::size_t j = 0;
    while(!file.eof()){
        for(std::size_t i = 0; i < T.Dim(); ++i){  
            file  >> T;
            Y.Put(T);
            ++j;
        }
    }
    this->points = new Vector(Y);
    file.close();
    return true;
}

template <typename Tf>
bool GnuFigure<Tf>::Draw(){
    this->Save(this->fileName);
    return this->Rysuj();
}

template <typename Tf>
void GnuFigure<Tf>::Rotate(const double &angle,  const std::size_t &x, const Vector<Tf> &v){
    double l = (angle / this->animateFPS) * M_PI/180;
    
    Matrix<double> M(Vector(cos(l), -sin(l)),
                    Vector(sin(l), cos(l)));

    for (std::size_t j = 0; j < x; j++){
        int i = 0;
        
        while(fabs(l*i) < fabs(angle) * M_PI/180){
            for (std::size_t d = 0; d < this->CountPoints(); d++){
                Vector u = (*this)[d];
                u = u - v;
                Vector w = M * u;
                (*this)[d] = w + v;
            }
            this->Draw();
            usleep(this->animateFPS == 1? 0 : 50000);
            i++;
        }
    }
    
}

template <typename Tf>
void GnuFigure<Tf>::Translate(const Vector<Tf> &v){
    Vector u(v);
    u =  u / this->animateFPS;
    std::cout << u << std::endl;; 
    int j = 0;
    while(fabs(u[0]*j) < fabs(v[0])){

        for(std::size_t i = 0; i < this->CountPoints(); i++)
            (*this->points)[i] = (*this->points)[i] + u;
        this->Draw();
        usleep(this->animateFPS == 1? 0 : 50000);
        ++j;
    }  
}

template <typename Tf>
void GnuFigure<Tf>::AddForce(const Vector<Tf> &v){
    this->force = this->force + v;
}

template <typename Tf>
void GnuFigure<Tf>::EveryFrame(){
    *this->force = Tf();

    (*this->force)[1] -= this->mass*GRAVITY;
    
    *this->velocity = *this->velocity +  *this->force * Tf(dt) / this->mass;


    // for(std::size_t i = 0; i< this->dim; ++i)
    //     (*this->velocity)[i] = (*this->velocity)[i] * dt;
    // *this->points = *(this->points) + *(this->velocity); 

    this->Draw();
}