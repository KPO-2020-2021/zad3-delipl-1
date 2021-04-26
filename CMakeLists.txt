# This file specifies how the project should be built, using CMake.
# If you are unfamiliar with CMake, don't worry about all the details.
# The sections you might want to edit are marked as such, and 
# the comments should hopefully make most of it clear.
#
# For many purposes, you may not need to change anything about this file.

cmake_minimum_required(VERSION 3.12)

# Set project name, version and laguages here. (change as needed)
# Version numbers are available by including "exampleConfig.h" in 
# the source. See exampleConfig.h.in for some more details.
project(CPP_BOILERPLATE VERSION 1.2.3.4 LANGUAGES CXX)


# Options: Things you can set via commandline options to cmake (e.g. -DENABLE_LTO=[ON|OFF])
option(ENABLE_WARNINGS_SETTINGS "Allow target_set_warnings to add flags and defines.
                                 Set this to OFF if you want to provide your own warning parameters." ON)
option(ENABLE_LTO "Enable link time optimization" ON)
option(ENABLE_DOCTESTS "Include tests in the library. Setting this to OFF will remove all doctest related code.
                        Tests in tests/*.cpp will still be enabled." ON)

# Include stuff. No change needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)
include(CTest)
include(Doctest)
include(Documentation)
include(LTO)
include(Misc)
include(Warnings)

# Check for LTO support.
find_lto(CXX)

# --------------------------------------------------------------------------------
#                          Compile Geometric Libraries 
# --------------------------------------------------------------------------------
add_library(VEC ./inc/Vector.h ./src/empty.cpp)
target_include_directories(VEC PUBLIC ./inc ./src)

add_library(MAT ./inc/Matrix.h ./src/empty.cpp)
target_link_libraries(MAT VEC)
target_include_directories(MAT PUBLIC ./inc ./src)

add_library(GNU ./inc/GnuPlotApi.hh ./src/GnuPlotApi.cpp)
target_include_directories(GNU PUBLIC ./inc)

add_library(FIG ./inc/Figure.h ./src/empty.cpp)
target_link_libraries(FIG MAT VEC GNU)
target_include_directories(FIG PUBLIC ./inc ./src)

add_library(MENU ./inc/Menu.h ./src/Menu.cpp)
target_include_directories(MENU PUBLIC ./inc)



# --------------------------------------------------------------------------------
#                         Locate files (change as needed).
# --------------------------------------------------------------------------------
set(LIBS MENU FIG)
set(TESTFILES        # All .cpp files in tests/
    tests/main.cpp
)

# --------------------------------------------------------------------------------
#                            Build! (Change as needed)
# --------------------------------------------------------------------------------


# Set the compile options you want (change as needed).
target_set_warnings(${LIBS} ENABLE ALL AS_ERROR ALL DISABLE Annoying)
# target_compile_options(${LIBRARY_NAME} ... )  # For setting manually.

# Add an executable for the file app/main.cpp.
# If you add more executables, copy these lines accordingly.
add_executable(main app/main.cpp)   # Name of exec. and location of file.

target_include_directories(main PRIVATE ./inc)
target_link_libraries(main PUBLIC ${LIBS})

target_set_warnings(main ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).
target_enable_lto(main optimized)  # enable link-time-optimization if available for non-debug configurations

# Set the properties you require, e.g. what C++ standard to use. Here applied to library and main (change as needed).
set_target_properties(
    ${LIBS} main 
      PROPERTIES 
        CXX_STANDARD 17 
        CXX_STANDARD_REQUIRED YES 
        CXX_EXTENSIONS NO
)

# Set up tests (see tests/CMakeLists.txt).
add_subdirectory(tests)
