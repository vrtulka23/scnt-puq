cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(PhysicalUnitsAndQuantities VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated -O3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# getting curret code version
#############################

execute_process(
    COMMAND bash -c "source settings.env && echo $CODE_VERSION"
    OUTPUT_VARIABLE CODE_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Version: ${CODE_VERSION}")

# compile example solvers
##########################

find_package(SCNT-EXS REQUIRED)

#get_directory_property(dirs INCLUDE_DIRECTORIES)
#message(STATUS "Global include directories: ${dirs}")
#message(STATUS "SCNT-EXS_INCLUDE_DIR ${SCNT-EXS_INCLUDE_DIR}")
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

# create libraries with selected modules

file(GLOB source_files "src/*.cpp" "src/**/*.cpp")
file(GLOB configs LIST_DIRECTORIES true "src/config-*.h")
foreach(config ${configs})
  get_filename_component(config_name ${config} NAME)
  message("Building library: ${config_name}")
  string(REGEX MATCH "^config-([a-z]+).h" matches ${config_name})
  set(lib_name "puqcpp-${CMAKE_MATCH_1}")
  add_library(${lib_name} STATIC ${source_files})
  target_compile_definitions(${lib_name} PRIVATE CONFIG_FILE="../src/${config_name}")
  #target_link_libraries(${lib_name} PRIVATE scnt-exs)
endforeach()

# create all executables

message("Compiling executable: puq")
file(GLOB example_files "exec/puq/*.cpp" "exec/puq/**/*.cpp")
add_executable(puq ${example_files} )
target_compile_definitions(puq PRIVATE CODE_VERSION="${CODE_VERSION}")
target_link_libraries(puq PRIVATE puqcpp-aef)

message("Compiling executable: dmap")
file(GLOB example_files "exec/dmap/*.cpp" "exec/dmap/**/*.cpp")
add_executable(dmap ${example_files} )
target_compile_definitions(dmap PRIVATE CODE_VERSION="${CODE_VERSION}")
target_link_libraries(dmap PRIVATE puqcpp-aef)

# install executables

install(TARGETS puq DESTINATION bin)

# add Google tests
###################

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# compile GTest tests
file(GLOB test_files "tests/*.cpp")

enable_testing()
add_executable(TestSolver ${test_files})
target_link_libraries(TestSolver PRIVATE GTest::gtest_main puqcpp-aef)

include(GoogleTest)
gtest_discover_tests(TestSolver)

# add Google benchmark
######################

find_package(benchmark REQUIRED)
file(GLOB test_files "benchmark/*.cpp")
add_executable(Benchmark ${test_files})
target_link_libraries(Benchmark PRIVATE benchmark::benchmark puqcpp-aef)

# pybind11
###########

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})
find_package(pybind11 CONFIG)

pybind11_add_module(pypuq exec/pypuq/pypuq.cpp)
target_link_libraries(pypuq PRIVATE puqcpp-aef)
