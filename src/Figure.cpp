#include <Figure.h>
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
void Figure<Tf>::Rotate(const double &angle, const Vector<Tf> &v)
{
    Matrix<Tf> M(Vector(Tf(cos(angle)), Tf(-sin(angle))),
                     Vector(Tf(sin(angle)), Tf(cos(angle))));
    for (std::size_t i = 0; i < this->CountPoints(); i++)
    {
        Vector u = (*this->points)[i];
        u = u - v;
        Vector w = M * u;
        (*this->points)[i] = w + v;
    }
}

/* -------------------------------------------------------------------------- */
/*                              FIGURE OPERATORS                              */
/* -------------------------------------------------------------------------- */
// in header
// virtual Vector<Tf> Figure<Tf>::operator[](const std::size_t &index) const{
// virtual Tf Figure<Tf>::operator()(const std::size_t &n, const std::size_t &m) const{

template <typename Tf>
std::ostream &operator<<(std::ostream &cout, Figure<Tf> &figure)
{
    for (std::size_t i = 0; i < figure.CountPoints(); i++){
        for (std::size_t j = 0; j < figure.Dimention(); j++)
            cout << std::setw(16) << std::fixed << std::setprecision(10) << figure(i, j);
        cout << std::endl;
    }
    for (std::size_t j = 0; j < figure.Dimention(); j++)
        cout << std::setw(16) << std::fixed << std::setprecision(10) << figure(0, j);
    cout << std::endl;
    return cout;
    }

template <typename Tf>
std::istream &operator>>(std::istream &cin, Figure<Tf> &figure)
{
    for (std::size_t i = 0; i < figure.CountPoints(); i++)
    {
        cin >> (*figure.points)[i];
        if (!cin)
            throw std::logic_error("Can't read Rectangle");
    }
    return cin;
}

/* -------------------------------------------------------------------------- */
/*                           RECTANGLE CONSTRUCTORS                           */
/* -------------------------------------------------------------------------- */
template <typename Tf>
Rectangle<Tf>::Rectangle(const Vector<Tf> &A, const Vector<Tf> &B, const Vector<Tf> &C, const Vector<Tf> &D)
{
    this->name = "Rectangle";
    Tf x = (A - B) * (A - D);
    Tf y = (C - D) * (C - B);
    if (x != Tf() || y != Tf())
        throw std::logic_error("Can't create rectangle");
    this->points = new Matrix(A, B, C, D);
}

template <typename Tf>
Rectangle<Tf>::Rectangle(const Tf &a, const Tf &b)
{
    this->name = "Rectangle";
    this->points = new Matrix(Vector(Tf(), Tf()), Vector(Tf(), a), Vector(b, Tf()), Vector(a, b));
}

/* -------------------------------------------------------------------------- */
/*                             RECTANGLE OPERATORS                            */
/* -------------------------------------------------------------------------- */
template <typename Tf>
std::istream &operator>>(std::istream &cin, Rectangle<Tf> &figure)
{
    double x, y;
    cin >> x;
    if (!cin)
        throw std::logic_error("Can't read Rectangle");
    cin >> y;
    if (!cin)
        throw std::logic_error("Can't read Rectangle");
    figure = Rectangle(x, y);
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
    this->tmpFile = new std::ofstream();

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
        this->tmpFile->open(fileName);
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
void GnuFigure<Tf>::Rotate(const double &angle, const Vector<Tf> &v){
    double x = M_PI/180;
    int i = 0;
    while(x*i < angle){
        Matrix<double> M(Vector(cos(x), -sin(x)),
                        Vector(sin(x), cos(x)));
        for (std::size_t i = 0; i < this->CountPoints(); i++){
            Vector u = (*this)[i];
            u = u - v;
            Vector w = M * u;
            (*this)[i] = w + v;
        }
        this->Save(this->fileName);
        // this->PrzeslijDoGNUPlota("\nreplot\n");
        std::cout << *this;
    
        usleep(100000);
        i++;
    }
}

template <typename Tf>
void GnuFigure<Tf>::PGMtoDAT(const std::string &pgmFileName){
    std::fstream pgmFile;
    pgmFile.open(pgmFileName);
    if(!pgmFile.good())
        throw std::logic_error("Can't open file");
    

}