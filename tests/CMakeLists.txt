cmake_minimum_required(VERSION 3.12)

# List all files containing tests. (Change as needed)
set(TESTFILES        # All .cpp files in tests/
    main.cpp
    dummy.cpp
)
add_executable(ut-vector test1.cpp)
target_link_libraries(ut-vector PUBLIC  doctest VEC MAT FIG)
target_include_directories(ut-vector PRIVATE ../lib/doctest ../src ../inc)
u
set_target_properties(ut-vector PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_set_warnings(ut-vector ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).

set_target_properties(ut-vector PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME ${LIBRARY_NAME}.ut-vector
    COMMAND ut-vector ${TEST_RUNNER_PARAMS})


set(TEST_MAIN unit_tests)   # Default name for test executable (change if you wish).
set(TEST_RUNNER_PARAMS "")  # Any arguemnts to feed the test runner (change as needed).

# --------------------------------------------------------------------------------
#                         Make Tests (no change needed).
# --------------------------------------------------------------------------------
add_executable(${TEST_MAIN} ${TESTFILES})
target_link_libraries(${TEST_MAIN} PUBLIC doctest Complex VEC MAT FIG)

# added libraries in ./lib ;)
target_include_directories(${TEST_MAIN} PRIVATE ../lib/doctest ../lib/Complex ../src ../inc)

set_target_properties(${TEST_MAIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_set_warnings(${TEST_MAIN} ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).

set_target_properties(${TEST_MAIN} PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
)

add_test(
    # Use some per-module/project prefix so that it is easier to run only tests for this module
    NAME ${LIBRARY_NAME}.${TEST_MAIN}
    COMMAND ${TEST_MAIN} ${TEST_RUNNER_PARAMS})

# Adds a 'coverage' target.
include(CodeCoverage)

