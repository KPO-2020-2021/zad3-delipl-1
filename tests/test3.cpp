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
    CHECK_NOTHROW(Figure t("Trojkat", A, B, C));
    
    Figure t("Trojkat", A, B, C);
    CHECK(t.Name() == "Trojkat");
    CHECK(t[0] == A);
    CHECK(t[1] == B);
    CHECK(t[2] == C);
    
}
TEST_CASE("2. Cross product") {
    Vector A(3, 2, 0);
    Vector B(4, 4, 0);
    Vector C(0, 0, 4);
    CHECK(operator&(A,B) == C);
}
TEST_CASE("3. Rotate Rectangle"){
    Vector A(0.0, 0.0);
    Vector B(0.0, 6.0);
    Vector C(4.0, 6.0);
    Vector D(4.0, 0.0);
    Figure R("d",A, B, C, D);
    R.Rotate(M_PI/2);
    // std::cout << R;
    CHECK(R[0] == Vector(0.0, 0.0));
    CHECK(R[1] == Vector(-6.0, 0.0));
    CHECK(R[2] == Vector(-6.0, 4.0));
    CHECK(R[3] == Vector(0.0, 4.0));

    R.Rotate(M_PI, 1,Vector(-3.0, 2.0));

    CHECK(R[2] == Vector(0.0, 0.0));
    CHECK(R[3] == Vector(-6.0, 0.0));
    CHECK(R[0] == Vector(-6.0, 4.0));
    CHECK(R[1] == Vector(0.0, 4.0));
}
TEST_CASE("4. Figure Translation"){
    Vector A(0.0, 0.0);
    Vector B(0.0, 6.0);
    Vector C(4.0, 6.0);
    Vector D(4.0, 0.0);
    Figure R("d",A, B, C, D);
    R.Translate(B);
    CHECK(R[0] == Vector(0.0, 6.0));
    CHECK(R[1] == Vector(0.0, 12.0));
    CHECK(R[2] == Vector(4.0, 12.0));
    CHECK(R[3] == Vector(4.0, 6.0));
}
TEST_CASE("5. GnuFigure constructor with opening file and checking points")
{
    CHECK_NOTHROW(GnuFigure<double> p("prostokat.dat", 2));
}
