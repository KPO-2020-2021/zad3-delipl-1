#include <Figure.h>
#include <limits>
#include <iomanip> 
/* -------------------------------------------------------------------------- */
/*                             FIGURE CONSTRUCTORS                            */
/* -------------------------------------------------------------------------- */
template <typename Tf>
template <class... Tv>
Figure<Tf>::Figure(const std::string &name, const Vector<Tf> &first, const Tv... args)
{
    this->name = name;
    this->points = new Matrix(first, args...);
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
template <typename Tf>
GnuFigure<Tf>::GnuFigure(){
    this->tmpFile = nullptr;
    this->points = nullptr;
}
template <typename Tf>
template <typename... Tv>
GnuFigure<Tf>::GnuFigure(const std::string &fileName, const Vector<Tf> &first, const Tv... args)
{
    this->UsunOstatniaNazwe();
    this->UsunOstatniaNazwe();
    this->fileName = std::string("../tmp/") + fileName + std::string(".dat");
    this->tmpFile = new std::fstream();

    this->points = new Matrix(first, args...);
    this->DodajNazwePliku(this->fileName.c_str(), PzG::RR_Ciagly, 2);

    this->DodajNazwePliku(this->fileName.c_str(), PzG::RR_Punktowy, 2);
    
    this->_Xmax = 200;
    this->_Xmin = -200;
    this->_Ymax = 225/2;
    this->_Ymin = -225/2; 
    
    this->ZmienTrybRys(PzG::TR_2D);
}

template <typename Tf>
GnuFigure<Tf>::GnuFigure(const std::string &fileName, const std::size_t &dim){
    this->UsunOstatniaNazwe();
    this->UsunOstatniaNazwe();
    this->fileName = std::string("../tmp/") + fileName;
    this->DodajNazwePliku(this->fileName.c_str(), PzG::RR_Ciagly, 2);
    this->DodajNazwePliku(this->fileName.c_str(), PzG::RR_Punktowy, 2);
    
    this->_Xmax = 200;
    this->_Xmin = -200;
    this->_Ymax = 225/2;
    this->_Ymin = -225/2; 

    this->tmpFile = new std::fstream();
    // std::cout << "NAME " << fileName+".dat";

    this->tmpFile->open("../datasets/"+fileName+".dat", std::ios::in);
    if(!this->tmpFile->good())
        throw std::logic_error("File not found");

    Vector<Vector<Tf>> Y;
    Vector<Tf> T;
    for(std::size_t i = 0; i < dim; ++i)
        T.Put(Tf());
    
    while(!tmpFile->eof()){
        for(std::size_t i = 0; i < dim; ++i){  
            (*tmpFile) >> T;
            Y.Put(T);
        }
    }
    this->tmpFile->close(); 

    this->points = new Matrix(Y);
}

template <typename Tf>
GnuFigure<Tf>::~GnuFigure(){
    delete this->tmpFile;
}

/* -------------------------------------------------------------------------- */
/*                              GNUFIGURE METHODS                             */
/* -------------------------------------------------------------------------- */
template <typename Tf>
bool GnuFigure<Tf>::Save(const std::string &fileName){
    
    if(this->tmpFile->is_open())
        *this->tmpFile << *this;
    else{
        this->tmpFile->open(fileName, std::ios::in);
        *this->tmpFile << *this;

    }
    this->tmpFile->close();
    return true;
}
template <typename Tf>
bool GnuFigure<Tf>::Draw()
{
    this->Save(this->fileName);
    
    return this->Rysuj();
}

template <typename Tf>
void GnuFigure<Tf>::Rotate(const double &angle,  const std::size_t &x, const Vector<Tf> &v){
    double y = angle* M_PI/180;
    // int i = 0;
    // while(x*i < angle){
    //     Matrix<double> M(Vector(cos(x), -sin(x)),
    //                     Vector(sin(x), cos(x)));
    //     for (std::size_t i = 0; i < this->CountPoints(); i++){
    //         Vector u = (*this)[i];
    //         u = u - v;
    //         Vector w = M * u;
    //         (*this)[i] = w + v;
    //     }
    //     // this->Save(this->fileName);
    //     this->Draw();
    //     std::cout << *this;
    
    //     usleep(100000);
    //     i++;
    // }
    Matrix M(Vector(cos(y), -sin(y)),
             Vector(sin(y), cos(y)));
    for (std::size_t j = 0; j <x; j++){
        for (std::size_t i = 0; i < this->CountPoints(); i++){
            Vector u = (*this)[i];
            u = u - v;
            Vector w = M * u;
            (*this)[i] = w + v;
        }
    }
}
