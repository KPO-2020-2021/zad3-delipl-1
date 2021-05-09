#include "doctest.h"
#include <fstream>
#include "Object.hpp"
TEST_CASE("1. Transform constructor"){
    CHECK_NOTHROW(Transform trans);
    Transform trans;
    CHECK(trans.position == Vector3());
    CHECK(trans.angles == Vector3());
    CHECK(trans.scale == Vector3({1, 1, 1}));
}
TEST_CASE("2. Object constriuctor, open file and read data"){
    CHECK_NOTHROW(Object rect("prostokat.dat", 4));
    Object rect("prostokat.dat", 4);

    CHECK(rect.Name() == "prostokat.dat");
    CHECK(rect.CountPoints() == 4);

    CHECK(rect[0] == Vector3({60, 60, 60}));
    CHECK(rect[1] == Vector3({210, 60, 60}));
    CHECK(rect[2] == Vector3({210, 160, 60}));
    CHECK(rect[3] == Vector3({60, 160, 60}));
    CHECK_THROWS(rect[4] == Vector3());

    CHECK_NOTHROW(rect.Save());
    CHECK_THROWS_AS(Object rect("nonExistsFile.dat", 4), std::exception);
}

// TEST_CASE("3. Apply physics test"){
//     Object rect("prostokat.dat", 4);
//     rect.force = Vector3({1000, 0, 0});
//     rect.ApplyPhysics();
//     rect.solid = true;

//     CHECK(rect.velocity == Vector3({15, 0, 0}));

//     CHECK(rect[0] == Vector3({60.225, 60, 60}));
//     CHECK(rect[1] == Vector3({210.225, 60, 60}));
//     CHECK(rect[2] == Vector3({210.225, 160, 60}));
//     CHECK(rect[3] == Vector3({60.225, 160, 60}));
// }

TEST_CASE("4. Object 8 points "){
    CHECK_NOTHROW(Object rect("prostopadloscian.dat", 8));
}