cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(PhysicalUnitsAndQuantities VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENV{PATH} "settings.env")

# compile example solvers
##########################

file(GLOB examples LIST_DIRECTORIES true "examples/*")
foreach(dirpath ${examples})

  get_filename_component(dirname ${dirpath} NAME)
  message("Compiling example: ${dirname}")
  file(GLOB source_files "src/*.h" "src/*.cpp" "src/**/*.h" "src/**/*.cpp")
  file(GLOB example_files "examples/${dirname}/*.h" "examples/${dirname}/*.cpp"
                          "examples/${dirname}/**/*.h" "examples/${dirname}/**/*.cpp")
  add_executable(${dirname} ${source_files} ${example_files} )

endforeach()

# add Google tests
###################

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# compile tests
################

file(GLOB test_files "tests/*.h" "tests/*.cpp")
#list(REMOVE_ITEM source_files "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

enable_testing()
add_executable(
   TestSolver
   ${test_files}
   ${source_files}
)
target_link_libraries(TestSolver GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TestSolver)
