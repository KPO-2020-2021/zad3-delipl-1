#include "doctest.h"
#include "Scene.hpp"

#include <limits>
extern bool DISPLAY;

TEST_CASE("1. Scene constructor"){
    CHECK_NOTHROW(Scene scene);
}
// Bad test

// TEST_CASE("2. Add object to scene"){
//     Scene scene;
//     Object rect("prostokat.dat", 4);
//     CHECK_NOTHROW(scene.AddObject(rect));

//     scene.AddObject(rect);
//     rect.force = Vector3({1000, 0, 0});
//     scene[0].ApplyPhysics();
//     CHECK(scene[0][0] == Vector3({60.225, 60, 60}));
//     CHECK(scene[0][1] == Vector3({210.225, 60, 60}));
//     CHECK(scene[0][2] == Vector3({210.225, 160, 60}));
//     CHECK(scene[0][3] == Vector3({60.225, 160, 60}));
// }

TEST_CASE("3. Draw Rectangle"){
    Scene scene;
    Object rect("prostokat.dat", 4);

    CHECK_NOTHROW(scene.AddObject(rect));

   if(DISPLAY){
        scene.Update();
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
    }
  
}

TEST_CASE("4. Draw gravitation"){
    Scene scene;
    Object cuboid("cube.dat", 16);
    CHECK_NOTHROW(scene.AddObject(cuboid));

    if(DISPLAY){
        scene.Update();
        std::cout << scene[0] << std::endl;
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<int>().max(), '\n');
    }
}