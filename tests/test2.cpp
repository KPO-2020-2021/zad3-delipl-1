#ifndef TESTRUNNER_CPP
    #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
    #include "doctest.h"
#endif
#include "Matrix.h"
TEST_CASE("1. Matrix default constructor"){
    CHECK_NOTHROW(Matrix<int> M());
}
TEST_CASE("2. Matrix constructor") {
    Vector v(5, 3);
    Vector u(6, 4);
    CHECK_NOTHROW( Matrix M(v, u));
}
TEST_CASE("3. Matrix cascade operator [n][m]") {
    Vector v(5, 3);
    Vector u(6, 4);
    Matrix M(v, u);
    CHECK(M[0][0] == 5);
    CHECK(M[0][1] == 3);
    CHECK(M[1][0] == 6);
    CHECK(M[1][1] == 4);
}
TEST_CASE("4. Matrix * Vector"){
    Matrix M(Vector(5, 3),
             Vector(2, 1));
    Vector v(0, 1);
    Vector u = M*v;
    CHECK(u[0] == 3);
    CHECK(u[1] == 1);
}

TEST_CASE("5. Matrix operator [] take row"){
    Matrix M(Vector(5, 3),
             Vector(2, 1));
    CHECK(M[0] == Vector(5, 3));
    CHECK_THROWS(M[2]);
}
TEST_CASE("6. Matrix check different Dim of Vectors"){
    Vector v(0, 1);
    Vector u(5, 3 ,4);
    CHECK_THROWS_AS(Matrix N(u, v), std::exception);
}
TEST_CASE("7. Matrix CrossPrepare of 2x3"){
    Vector v(4, 4, 0);
    Vector u(6, 4, 0);
    Vector x = Matrix(v, u).CrossPrepare();
    Vector w(0, 0, -8);
    CHECK(x == w);
}
TEST_CASE("8. Matrix Vector of Vector Constructor"){
    Vector v(Vector(5, 4), Vector(3, 6));
    CHECK_NOTHROW(Matrix M(v));
    Matrix M(v);
    CHECK(M[0][0] == 5);
    CHECK(M[0][1] == 4);
    CHECK(M[1][0] == 3);
    CHECK(M[1][1] == 6);
}
TEST_CASE("9. Matrix det of 3x3"){
    Matrix R(Vector(2.0, 3.0),
             Vector(5.0, 1.0));
    CHECK(R.Det() == -13); 
}
TEST_CASE("10. Matrix flip function"){
    Matrix R(Vector(2.0, 3.0),
             Vector(5.0, 1.0),
             Vector(6.0, 3.0));
    Matrix M(Vector(2.0, 5.0, 6.0),
             Vector(3.0, 1.0, 3.0));
    CHECK(M[0] == R.Flip()[0]); 
    CHECK(M[1] == R.Flip()[1]); 
}
TEST_CASE("10. Multiplar Matrix"){
    Matrix M(Vector(1,2,3),
            Vector(4,5,6));

    Matrix N(Vector(7, 8),
             Vector(9, 10),
             Vector(11, 12));
    Matrix W(M*N);
    // CHECK(W);
}