#include "doctest.h"

#include "Matrix3x3.hpp"
TEST_CASE("1. Matrix default constructor"){
    CHECK_NOTHROW(Matrix<int, 3, 15> M());
    CHECK_NOTHROW(Matrix2x2 M);
    CHECK_NOTHROW(Matrix3x3 M);
}
TEST_CASE("2. Matrix constructor") {
    Vector2 v({5, 3});
    Vector2 u({6, 4});
    CHECK_NOTHROW(Matrix2x2 M({v, u}));
}
TEST_CASE("3. Matrix cascade operator [n][m]") {
    Vector2 v({5, 3});
    Vector2 u({6, 4});
    Matrix2x2 M({v, u});
    CHECK(M[0][0] == 5);
    CHECK(M[0][1] == 3);
    CHECK(M[1][0] == 6);
    CHECK(M[1][1] == 4);
}
TEST_CASE("4. Matrix * Vector"){
    Matrix2x2 M({Vector2({5, 3}),
                Vector2({2, 1})});
    Vector2 v({0, 1});
    Vector2 u = M*v;
    CHECK(u[0] == 3);
    CHECK(u[1] == 1);
}
TEST_CASE("5. Matrix operator [] take row"){
    Matrix2x2 M({{5, 3},
                {2, 1}});
    CHECK(M[0] == Vector2({5, 3}));
    CHECK_THROWS(M[2]);
}
TEST_CASE("6. Matrix det"){
    Matrix2x2 R  = {    {2, 3},
                        {5, 1}};
    CHECK(R.Det() == -13); 
}
TEST_CASE("10. Matrix flip function"){
    Matrix<double, 3, 2>  R({{2.0, 3.0},
                             {5.0, 1.0},
                             {6.0, 3.0}});
    Matrix<double, 2 ,3> M({{2.0, 5.0, 6.0},
                            {3.0, 1.0, 3.0}});
    CHECK(M[0] == R.Flip()[0]); 
    CHECK(M[1] == R.Flip()[1]); 
}
TEST_CASE("10. Multiplar Matrix"){
    Matrix<double, 2, 3> M =  {{1,2,3},
                               {4,5,6}};

    Matrix<double,3,2> N = {{7, 8},
                            {9, 10},
                            {11, 12}};
    Matrix<double, 2, 2> W(M*N);
    CHECK(W[0][0] == 58);
    CHECK(W[0][1] == 64);
    CHECK(W[1][0] == 139);
    CHECK(W[1][1] == 154);
}