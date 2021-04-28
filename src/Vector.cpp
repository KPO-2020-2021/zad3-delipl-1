#include <cmath>
#include <limits>
#include "Vector.h"
#ifndef MIN_DIFF
    #define MIN_DIFF 0.0000001
#endif

/* -------------------------------------------------------------------------- */
/*                                CONSTRUCTORS                                */
/* -------------------------------------------------------------------------- */
template <typename Tf>
Vector<Tf>::Vector() {
    this->value = nullptr;
    this->dim = 0;
}
template <typename Tf>
Vector<Tf>::Vector(const Vector &v) {
    this->dim = v.Dim();
    this->value = new Tf[v.Dim()];
    for (std::size_t i = 0; i < this->dim; i++) {
        this->value[i] = v[i];
    }
}

template <typename Tf>
template <typename... T>
Vector<Tf>::Vector(const Tf &first, const T... args) {
    this->dim = sizeof...(args) + 1;
    this->value = new Tf[this->dim];
    this->value[0] = first;
    Tf tempTab[] = {args...};
    for (std::size_t i = 1; i < this->dim; i++)
        this->value[i] = tempTab[i - 1];
}

template <typename Tf>
Vector<Tf>::Vector(const Tf &first){
    this->dim =  1;
    this->value = new Tf[this->dim];
    this->value[0] = first;
}

template <typename Tf>
Vector<Tf>::~Vector() {
        if (this->value != nullptr)
            delete [] this->value;
}

/* -------------------------------------------------------------------------- */
/*                                   METHODS                                  */
/* -------------------------------------------------------------------------- */
template <typename Tf>
std::size_t Vector<Tf>::Dim() const {
    return this->dim;
}

template <typename Tf>
Tf Vector<Tf>::Length() const {
    Tf x = Tf();
    for (std::size_t i = 0; i < this->dim; i++)
        x += this->value[i] * this->value[i];
    return sqrt(x);
}

template <typename Tf>
void Vector<Tf>::Put(const Tf &value) {
    Tf *ptr = this->value;
    this->dim++;
    this->value = new Tf[this->dim];
    for (std::size_t i = 0; i < this->dim - 1; i++)
        this->value[i] = Tf(ptr[i]);
    this->value[this->dim - 1] = Tf(value);
}

template <typename Tf>
Tf Vector<Tf>::Pop() {
    Tf *ptr = this->value;
    this->dim--;
    this->value = new Tf[this->dim];
    for (std::size_t i = 0; i < this->dim; i++)
    {
        this->value[i] = Tf(ptr[i]);
    }
    Tf x = ptr[this->dim];
    delete (ptr);
    return x;
}

template <typename Tf>
Tf Vector<Tf>::Remove(const std::size_t index){
    if(index >= this->dim)
        throw std::out_of_range("Try to remove on index out of range");
    Tf *ptr = this->value;
    this->dim--;
    Tf x(ptr[index]);
    this->value = new Tf[this->dim];
    for (std::size_t i = 0; i < this->dim; i++)
    {
        if (i >= index){
            this->value[i] = Tf(ptr[i+1]);
        }
        else{
            this->value[i] = Tf(ptr[i]);
        }
    }
    return x;
}

/* -------------------------------------------------------------------------- */
/*                                  OPERATORS                                 */
/* -------------------------------------------------------------------------- */
template <typename Tf>
Tf Vector<Tf>::operator[](const std::size_t &i) const {
    if (i >= this->dim)
        throw std::out_of_range("Vector out of range");
    return value[i];
}
template <typename Tf>

Tf &Vector<Tf>::operator[](const std::size_t &i){
    if (i >= this->dim)
        throw std::out_of_range("Vector out of range");
    return value[i];
}

template <typename Tf>
bool Vector<Tf>::operator==(const Vector &v) const {
    for (std::size_t i = 0; i < this->dim; i++)
        if (this->value[i] != v[i])
            return false;
    return true;
}

template <typename Tf>
bool Vector<Tf>::operator!=(const Vector &v) const {
    for (std::size_t i = 0; i < this->dim; i++)
        if (this->value[i] != v[i])
            return true;
    return false;
}

template <typename Tf>
bool Vector<Tf>::operator!() const {
    return this->value == nullptr || this->dim == 0;
}

template <typename Tf>
Vector<Tf> &Vector<Tf>::operator=(const Vector &v) {
    this->dim = v.Dim();
    if(this->value != nullptr)
        delete (this->value);
    this->value = new Tf[v.Dim()];
    for (std::size_t i = 0; i < this->dim; i++)
        this->value[i] = Tf(v[i]);
    return *this;
}

template <typename Tf>
Vector<Tf> Vector<Tf>::operator+(const Vector &v) const {
    Vector u(v);
    for (std::size_t i = 0; i < this->dim; i++)
        u.value[i] += this->value[i];
    return u;
}
template <typename Tf>
Vector<Tf> Vector<Tf>::operator-(const Vector &v) const {
    Vector u(v);
    for (std::size_t i = 0; i < this->dim; i++)
        u.value[i] = this->value[i] - u[i];
    return u;
}
template <typename Tf>
Vector<Tf> Vector<Tf>::operator*(const Tf &k) {
    Vector u(*this);
    for (std::size_t i = 0; i < this->dim; i++){
        u.value[i] = k * this->value[i];
    }
    return u;
}
template <typename Tf>
Vector<Tf> Vector<Tf>::operator/(const Tf &k) {
    Vector u(*this);
    for (std::size_t i = 0; i < this->dim; i++)
        u.value[i] = this->value[i] / k;
    return u;
}

template <typename Tf>
Tf Vector<Tf>::operator*(const Vector &v) {
    Tf x = Tf();
    for (std::size_t i = 0; i < this->dim; i++)
        x += this->value[i] * v[i];
    return x;
}
template <>
double Vector<double>::operator*(const Vector &v) {
    double x = double();
    for (std::size_t i = 0; i < this->dim; i++)
        x += this->value[i] * v[i];

    double re = (std::size_t)(x * pow(MIN_DIFF, -1));
    re = x * pow(MIN_DIFF, -1);
    re = round(re);
    re = re * MIN_DIFF;

    return re;
    // return x;
}

template <typename Tf>
std::ostream &operator<<(std::ostream &cout, const Vector<Tf> &v) {
    if (v.Dim() == 0) {
        return cout << "[null]";
    }
    cout << "[";
    if(v.Dim() > 1){
        cout << v[0] << ", ";
        for (std::size_t i = 1; i < v.Dim() - 1; i++) {
            cout << v[i] << ", ";
        }
        cout << v[v.Dim() - 1];
    }
    else{
        cout << v[0];
    }
    cout << "]";
    return cout;
}

template <typename Tf>
std::istream &operator>>(std::istream &cin, Vector<Tf> &v) {
    char c;
    std::size_t i = 0;
    while(i < v.Dim()){
        cin >> c;
        if (!cin)
            return cin;
        if(c == '\n' || c == EOF)
            return cin;
        cin.putback(c);
        Tf x;
        cin >> x;
        if (!cin)
            throw std::logic_error("Vector input error");
        v[i] = x;
        ++i;
    }
    return cin;
}