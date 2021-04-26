cmake_minimum_required(VERSION 3.12)

# List all files containing tests. (Change as needed)
set(TESTFILES        # All .cpp files in tests/
    main.cpp
    dummy.cpp
    # your new file
)

set(INC ../lib/doctest ../src ../inc)
#  -------------------------------------------------------------------------- 
#                               TEST VECTOR CLASS                             
#  -------------------------------------------------------------------------- 

add_executable(ut-vector test1.cpp)
target_link_libraries(ut-vector PUBLIC  doctest VEC)
target_include_directories(ut-vector PRIVATE ${INC})
set_target_properties(ut-vector PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_set_warnings(ut-vector ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).

set_target_properties(ut-vector PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
)

#  -------------------------------------------------------------------------- 
#                               TEST MATRIX CLASS                             
#  -------------------------------------------------------------------------- 

add_executable(ut-matrix test2.cpp)
target_link_libraries(ut-matrix PUBLIC  doctest MAT)
target_include_directories(ut-matrix PRIVATE ${INC})
set_target_properties(ut-matrix PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_set_warnings(ut-matrix ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).

set_target_properties(ut-matrix PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
)

#  -------------------------------------------------------------------------- 
#                              TEST FIGURE CLASS                             
#  -------------------------------------------------------------------------- 
add_executable(ut-figure test3.cpp)
target_link_libraries(ut-figure PUBLIC  doctest FIG)
target_include_directories(ut-figure PRIVATE ${INC})
set_target_properties(ut-figure PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_set_warnings(ut-figure ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).

set_target_properties(ut-figure PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
)
#  -------------------------------------------------------------------------- 
#                              TEST MENU CLASS                             
#  -------------------------------------------------------------------------- 
add_executable(ut-menu test4.cpp)
target_link_libraries(ut-menu PUBLIC  doctest MENU)
target_include_directories(ut-menu PRIVATE ${INC})
set_target_properties(ut-menu PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_set_warnings(ut-figure ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).

set_target_properties(ut-menu PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
)
# --------------------------------------------------------------------------------
#                         Make Tests (no change needed).
# --------------------------------------------------------------------------------
set(TEST_MAIN unit_tests)   # Default name for test executable (change if you wish).
set(TEST_RUNNER_PARAMS "")  # Any arguemnts to feed the test runner (change as needed).

add_executable(${TEST_MAIN} ${TESTFILES})
target_link_libraries(${TEST_MAIN} PUBLIC doctest ${LIBS})


set_target_properties(${TEST_MAIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_set_warnings(${TEST_MAIN} ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).

set_target_properties(${TEST_MAIN} PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
)

# Adds a 'coverage' target.
include(CodeCoverage)

