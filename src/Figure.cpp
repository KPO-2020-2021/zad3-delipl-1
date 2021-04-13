#include<Figure.h>
/* -------------------------------------------------------------------------- */
/*                             FIGURE CONSTRUCTORS                            */
/* -------------------------------------------------------------------------- */
template <typename Tf>
template <class... Tv>
Figure<Tf>::Figure(const std::string &name, const Vector<Tf> &first, const Tv... args) {
    this->name = name;
    this->points = new Matrix(first, args...);
}
template <typename Tf>
Figure<Tf>::Figure() {
}

template <typename Tf>
Figure<Tf>::~Figure() {
    delete this->points;
}

/* -------------------------------------------------------------------------- */
/*                               FIGURE METHODS                               */
/* -------------------------------------------------------------------------- */
template <typename Tf>
void Figure<Tf>::Rotate(const double &angle, const Vector<Tf> &v) {
    Matrix<double> M(Vector(cos(angle), -sin(angle)),
                     Vector(sin(angle), cos(angle)));
    for (int i = 0; i < this->CountPoints(); i++) {
        Vector u = (*this->points)[i];
        u = u - v;
        Vector w = M * u;
        (*this->points)[i] = w + v;
    }
}

/* -------------------------------------------------------------------------- */
/*                              FIGURE OPERATORS                              */
/* -------------------------------------------------------------------------- */
template <typename Tf>
std::ostream &operator<<(std::ostream &cout, Figure<Tf> &figure) {
    char c = 'A';
    cout << figure.Name() << ": ";
    for (int i = 0; i < figure.CountPoints()-1; i++) {
        Vector<Tf> v(figure[i] - figure[i + 1]);
        cout << "(" << v.Length() << ") ";
    }
    Vector<Tf> v(figure[figure.CountPoints()-1] - figure[0]);
    cout << "(" << v.Length() << ") ";
    for (int i = 0; i < figure.CountPoints(); i++) {
        cout << c << " = " << figure[i] << " ";
        c++;
    }
    return cout;
}

template <typename Tf>
std::istream &operator>>(std::istream &cin, Figure<Tf> &figure) {
    for (int i = 0; i < figure.CountPoints(); i++) {
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
Rectangle<Tf>::Rectangle(const Vector<Tf> &A, const Vector<Tf> &B, const Vector<Tf> &C, const Vector<Tf> &D) {
    this->name = "Rectangle";
    Tf x = (A - B) * (A - D);
    Tf y = (C - D) * (C - B);
    if (x != Tf() || y != Tf())
        throw std::logic_error("Can't create rectangle");
    this->points = new Matrix(A, B, C, D);
}

template <typename Tf>
Rectangle<Tf>::Rectangle(const Tf &a, const Tf &b) {
    this->name = "Rectangle";
    this->points = new Matrix(Vector(Tf(), Tf()), Vector(Tf(), a), Vector(b, Tf()), Vector(a, b));
}

/* -------------------------------------------------------------------------- */
/*                             RECTANGLE OPERATORS                            */
/* -------------------------------------------------------------------------- */
template <typename Tf>
std::istream &operator>>(std::istream &cin, Rectangle<Tf> &figure) {
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