#ifndef TESTRUNNER_CPP
    #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
    #include "doctest.h"
#endif
#include "Vector.h"
#include "Matrix.h"
#include "Figure.h"
TEST_CASE("1. Figure constructor and Name"){
    Vector A(3, 2);
    Vector B(4, 4);
    Vector C(9, 4);
    Figure t("Trojkat", A, B, C);
    CHECK(1==1);
    CHECK(t.Name() == "Trojkat");
}
TEST_CASE("3. Cross product") {
    Vector A(3, 2, 0);
    Vector B(4, 4, 0);
    Vector C(0, 0, 4);
    CHECK(operator&(A,B) == C);
}
TEST_CASE("4. Rectangle Constructor") {
    Vector A(0.0, 0.0);
    Vector B(0.0, 6.0);
    Vector C(4.0, 6.0);
    Vector D(4.0, 0.0);
    Vector Dp(2.0, 6.0);

    CHECK_NOTHROW(Rectangle R(A, B, C, D));
    CHECK_THROWS_AS(Rectangle R(A, B, C, Dp), std::exception);
    double x = 5;
    double y = 10;
    CHECK_NOTHROW(Rectangle R(x, y));
}
TEST_CASE("5. Figure print"){
    Vector A(3, 2);
    Vector B(4, 4);
    Vector C(9, 4);
    Figure t("Trojkat", A, B, C);
    std::ostringstream out;
    out << t;
    CHECK(out.str() == "Trojkat: (2) (5) (6) A = [3, 2] B = [4, 4] C = [9, 4] ");
}
TEST_CASE("6. Rectangle operator[]") {
    Vector A(0.0, 0.0);
    Vector B(0.0, 6.0);
    Vector C(4.0, 6.0);
    Vector D(4.0, 0.0);
    Rectangle R(A, B, C, D);
    CHECK(R[0] == A);
}
TEST_CASE("7. Rotate Rectangle"){
    Vector A(0.0, 0.0);
    Vector B(0.0, 6.0);
    Vector C(4.0, 6.0);
    Vector D(4.0, 0.0);
    Rectangle R(A, B, C, D);
    R.Rotate(M_PI/2);
    std::cout << R;
    CHECK(R[0] == Vector(0.0, 0.0));
    CHECK(R[1] == Vector(-6.0, 0.0));
    CHECK(R[2] == Vector(-6.0, 4.0));
    CHECK(R[3] == Vector(0.0, 4.0));
    R.Rotate(M_PI, Vector(-3.0, 2.0));
    CHECK(R[2] == Vector(0.0, 0.0));
    CHECK(R[3] == Vector(-6.0, 0.0));
    CHECK(R[0] == Vector(-6.0, 4.0));
    CHECK(R[1] == Vector(0.0, 4.0));
}