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

TEST_CASE("6. Rectangle operator[]") {
    Vector A(0.0, 0.0);
    Vector B(0.0, 6.0);
    Vector C(4.0, 6.0);
    Vector D(4.0, 0.0);
    Figure R("d",A, B, C, D);
    CHECK(R[0] == A);
}
TEST_CASE("7. Rotate Rectangle"){
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
TEST_CASE("8. Gnu figure constructor and draw"){
    Vector A(0.0, 0.0);
    Vector B(0.0, 60.0);
    Vector C(100.0, 60.0);
    Vector D(100.0, 0.0);
    // GnuFigure rectangle("rectangle", A, B, C, D);
    // rectangle.Draw();
}
TEST_CASE("9. Gnu figure constructor read"){
    GnuFigure<double> rectangle("prostokat", 2);
    std::cout << "DUPA" << rectangle << "DUPA";

}
TEST_CASE("10. Gnu figure rotate")
{
    Vector A(0.0, 0.0);
    Vector B(0.0, 60.0);
    Vector C(100.0, 60.0);
    Vector D(100.0, 0.0);
    GnuFigure Rec("rectangle", A, B, C, D);
    // Rec.Draw();
    // std::cout << "Naciśnij ENTER, aby kontynuowac" << std::endl;
    // std::cin.ignore(100000, '\n');
    // Rec.Draw();
    Rec.Rotate(M_PI / 2);
    
    std::cout << "Naciśnij ENTER, aby kontynuowac" << std::endl;
    std::cin.ignore(100000, '\n');
}
TEST_CASE("11. Gnu s rotate")
{
    Vector A(0.0, 0.0);
    Vector B(0.0, 100.0);
    Vector C(-100.0, 100.0);
    Vector D(0.0, 100.0);
    Vector E(0.0, 0.0);
    Vector F(100.0, 0.0);
    Vector G(100.0, 100.0);
    Vector H(100.0, 0.0);
    Vector I(0.0, 0.0);
    Vector J(-100.0, 0.0);
    Vector K(-100.0, -100.0);
    Vector L(-100.0, 0.0);
    Vector M(0.0, 0.0);
    Vector N(0.0, -100.0);
    Vector O(100.0, -100.0);
    Vector P(0.0, -100.0);
    GnuFigure X("X", A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P);
    X.Rotate(M_PI / 2);
    std::cout << "Naciśnij ENTER, aby kontynuowac" << std::endl;
    std::cin.ignore(100000, '\n');
}

