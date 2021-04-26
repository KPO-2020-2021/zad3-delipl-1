#ifndef TESTRUNNER_CPP
    #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
    #include "doctest.h"
#endif 
#include "Vector.h"

TEST_CASE("1. Vector default constructor"){
    Vector<int> x;
    CHECK(1 == 1);
}
TEST_CASE("2. Vector<Vector> table of Vectorrs"){
    Vector w(5, 6);
    Vector u(9, 4);
    Vector<Vector<int>> *v = new Vector(w, u);
    CHECK((*v)[0] == w);
}
TEST_CASE("100. Vector<Vector> 2 dimention   constructor"){
    Vector c(2);
    CHECK(c.Dim() == 1);
    Vector v(5, 3);
    Vector u(9, 4);
    Vector w(v, u);
    CHECK(w[0] == v);
}

TEST_CASE("3. Vector 2 dim constructor with tab"){
    Vector x(6, 9);
    CHECK_THROWS(x[2] == 6);
    CHECK_THROWS(x[-2] == 6);
}
TEST_CASE("4. Vector 2 dim constructor with tab"){
    Vector x(6, 9);

    CHECK((x.Dim() == 2 && x[0] == 6 && x[1] == 9));
}
TEST_CASE("5. Vector 6 dim constructor with tab"){
    Vector x(1, 2, 3, 4, 5, 6);

    CHECK(x.Dim() == 6);
}
TEST_CASE("8. Vector copy Constructor"){
    Vector v(5, -9, 3);
    Vector u(v);

    CHECK(u[0] == 5);
    CHECK(u[1] == -9);
    CHECK(u[2] == 3);
}
TEST_CASE("8. Vector == and !=operator"){
    Vector v(5, -9, 3);

    Vector u(v);
    Vector x(9, 3, 5);

    CHECK(v == u);
    CHECK(v != x);
}

TEST_CASE("8. Vector !operator if empty"){
    Vector<int> v;
    CHECK(!v == true);
    Vector u(5, 3);
    CHECK(!u == false);
}
TEST_CASE("9. Vector Length"){
    Vector u(4, 3);
    Vector v(8, -6, 5, 10);
    CHECK(u.Length() == 5);
    CHECK(v.Length() == 15);
}
TEST_CASE("10. Vector substraction and addition"){
    Vector u(4, 3);
    Vector z(6, -9);
    Vector v(10, -6);
    Vector x(-2, 12);
    CHECK(u + z == v);
    CHECK(u - z == x);
}

TEST_CASE("11. Vector multiplication and division")
{
    Vector u(4.0, -3.0);
    Vector x(-2.0, 1.5);
    Vector v(-8.0, 6.0);
    double z = -0.5;
    CHECK(u * z == x);
    CHECK(u / z == v);
}
TEST_CASE("12. Vector multiplication Vector by Vector") {
    Vector u(4.0, -3.0);
    Vector x(-2.0, 1.5);
    double z = -12.5;
    CHECK(u * x == z);
}

TEST_CASE("13. Vector pointner") {
    Vector<int> *v;
    Vector u(5);
    v= new Vector(u);
    CHECK(*v == u);
}
TEST_CASE("14. Vector pointner of Vector ") {
    Vector<Vector<int>> *v;
    Vector w(5, 6, 8);
    Vector u(w, w);
    v = new Vector(u);
    CHECK(*v == u);
}
TEST_CASE("15. Vector Put and Pop method"){
    Vector<int> v;
    int x = 69;
    v.Put(x);
    CHECK(v[0] == x);
    int y = -5;
    v.Put(y);
    CHECK(v[1] == y);
    int z = 3;
    v.Put(z);
    CHECK(v[0] == x);
    CHECK(v[1] == y);
    CHECK(v[2] == z);
    int k = v.Pop();
    CHECK(k == z);
    CHECK_THROWS(v[2]);
}
TEST_CASE("16. Vector Remove method") {
    Vector v(6, 3 ,9 ,5);
    int x = v.Remove(1);
    CHECK(x == 3);
    Vector u(6, 9, 5);
    CHECK(v == u);
    CHECK_THROWS(v.Remove(69));
}
// TEST_CASE("17. Vector Insert method"){
//     Vector v(1, 3);
//     v.Insert(1, 2);
//     CHECK(v[0] == 1);
//     CHECK(v[1] == 2);
//     CHECK(v[2] == 3);
//     CHECK_THROWS(v.Insert(5, 9));
// }
TEST_CASE("18. Vector remove Vector method") {
    Vector v(Vector (1, 3), Vector(2,3));

    v.Remove(0);

    std::ostringstream out;
    out << v;
    CHECK(out.str() == "[[2, 3]]");
    out << std::endl;
    v[0].Remove(0);
    std::ostringstream out1;
    out1 << v;
    CHECK(out1.str() == "[[3]]");
    CHECK(v[0] == Vector(3));
    CHECK(v.Dim() == 1);
    CHECK_THROWS(v[1]);
    CHECK(v[0].Dim() == 1);
    CHECK_THROWS(v[0][1]);
}
TEST_CASE("x. Vector input output") {
    Vector<int> x;
    std::istringstream in("[5, +9, -9, 16, 36]");
    in >> x;
    std::ostringstream out; 
    out << x;
    CHECK(out.str() == "[5, 9, -9, 16, 36]");
    in = std::istringstream("[6,32,5");
    CHECK_THROWS(in >> x);
}