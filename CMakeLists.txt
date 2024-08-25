cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(PhysicalUnitsAndQuantities VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated -O3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# compile example solvers
##########################

message(STATUS "Version: ${CODE_VERSION}")

#find_package(OpenMP COMPONENTS CXX REQUIRED)

file(GLOB source_files "src/*.cpp" "src/**/*.cpp")
add_library(puqcpp.eaf STATIC ${source_files})
#target_link_libraries(puqcpp.eaf PUBLIC OpenMP::OpenMP_CXX)

file(GLOB exec LIST_DIRECTORIES true "exec/*")
foreach(dirpath ${exec})
		
get_filename_component(dirname ${dirpath} NAME)
message("Compiling example: ${dirname}")
file(GLOB example_files "exec/${dirname}/*.cpp" "exec/${dirname}/**/*.cpp")
#  if(EXISTS "exec/${dirname}/config.h")
#    add_executable(${dirname} ${example_files} ${source_files} )
#    target_compile_definitions(${dirname} PRIVATE CODE_VERSION="${CODE_VERSION}")
#    target_compile_definitions(${dirname} PRIVATE CONFIG_FILE="../exec/${dirname}/config.h")
#  else()
add_executable(${dirname} ${example_files} )
#    if(OpenMP_CXX_FOUND)
#	target_link_libraries(${dirname} PUBLIC puqcpp.eaf OpenMP::OpenMP_CXX)
#    else()
        target_link_libraries(${dirname} puqcpp.eaf)
#    endif()	
target_compile_definitions(${dirname} PRIVATE CODE_VERSION="${CODE_VERSION}")
#endif()

endforeach()

#set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR})
#file(MAKE_DIRECTORY ${INSTALL_DIR}/include)
#file(MAKE_DIRECTORY ${INSTALL_DIR}/lib)
#file(MAKE_DIRECTORY ${INSTALL_DIR}/bin)
#file(COPY src/quantity.h DESTINATION ${INSTALL_DIR}/include)
#install(TARGETS libpuqcpp.eaf.a DESTINATION ${INSTALL_DIR}/lib)
install(TARGETS puq DESTINATION bin)

# add Google tests
###################

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# compile GTest tests
file(GLOB test_files "tests/*.cpp")
#list(REMOVE_ITEM source_files "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

enable_testing()
add_executable(TestSolver ${test_files})
target_link_libraries(TestSolver puqcpp.eaf)
target_link_libraries(TestSolver GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TestSolver)

# add Google benchmark
######################

find_package(benchmark REQUIRED)
file(GLOB test_files "benchmark/*.cpp")
add_executable(Benchmark ${test_files})
target_link_libraries(Benchmark PRIVATE benchmark::benchmark puqcpp.eaf)
