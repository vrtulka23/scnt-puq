cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(PUQ VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-deprecated -O3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MODULE_NAME scnt-puq)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_LIBDIR lib)
set(CMAKE_INSTALL_INCLUDEDIR include)

# compile libraries and executables
###################################

message("Code version: ${CODE_VERSION}")

find_package(SCNT-EXS REQUIRED)

message("Building library: puq-cpp")
file(GLOB source_files "src/*.cpp" "src/**/*.cpp")
add_library(puq-cpp STATIC ${source_files})
target_compile_definitions(puq-cpp PRIVATE CONFIG_FILE="../src/config.h")

message("Compiling executable: puq")
file(GLOB example_files "exec/puq/*.cpp" "exec/puq/**/*.cpp")
add_executable(puq ${example_files} )
target_compile_definitions(puq PRIVATE CODE_VERSION="${CODE_VERSION}")
target_link_libraries(puq PRIVATE puq-cpp)

message("Compiling executable: dmap")
file(GLOB example_files "exec/dmap/*.cpp" "exec/dmap/**/*.cpp")
add_executable(dmap ${example_files} )
target_compile_definitions(dmap PRIVATE CODE_VERSION="${CODE_VERSION}")
target_link_libraries(dmap PRIVATE puq-cpp)

# add Google tests
###################

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

file(GLOB test_files "gtest/*.cpp")
add_executable(TestSolver ${test_files})
target_link_libraries(TestSolver PRIVATE GTest::gtest_main puq-cpp)

include(GoogleTest)
gtest_discover_tests(TestSolver)

# add Google benchmark
######################

find_package(benchmark REQUIRED)

file(GLOB test_files "benchmark/*.cpp")
add_executable(Benchmark ${test_files})
target_link_libraries(Benchmark PRIVATE benchmark::benchmark puq-cpp)

# create pydipl module for Python
#################################

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})
find_package(pybind11 CONFIG)

pybind11_add_module(pypuq exec/pypuq/pypuq.cpp)
target_link_libraries(pypuq PRIVATE puq-cpp)
target_compile_definitions(pypuq PRIVATE CODE_VERSION="${CODE_VERSION}")

# create cmake export files
###########################

include(CMakePackageConfigHelpers)

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/${MODULE_NAME}-config.cmake.in
  	"${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}-config.cmake"
  	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${MODULE_NAME}
	PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}-config-version.cmake"
    	VERSION ${CODE_VERSION}
    	COMPATIBILITY AnyNewerVersion
)

# install files
###############

install(TARGETS puq EXPORT PuqTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${MODULE_NAME})

install(TARGETS puq-cpp EXPORT PuqTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})

install(TARGETS pypuq EXPORT PuqTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MODULE_NAME})
	
install(DIRECTORY src/
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${MODULE_NAME}
	FILES_MATCHING PATTERN "*.h")
	
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}-config-version.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${MODULE_NAME}
)

install(EXPORT PuqTargets
        FILE ${MODULE_NAME}-targets.cmake
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${MODULE_NAME}"
)

