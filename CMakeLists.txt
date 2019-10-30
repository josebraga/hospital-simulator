cmake_minimum_required(VERSION 3.14)
project(hospital-simulator)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCE src/*.cpp)
file(GLOB_RECURSE HEADER src/*.h)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE} ${HEADER})


################################
# Googletest
################################
set(TESTNAME test_Patient)
set(GTESTPATH ${CMAKE_SOURCE_DIR}/lib/googletest)

#enable_testing()
include_directories(${GTESTPATH}/include)

# Add test cpp file
add_executable( ${TESTNAME} ${HEADER} tests/test_Patient.cpp)

# Link test executable against gtest & gtest_main
target_link_libraries(${TESTNAME} ${GTESTPATH}/libgtest.a ${GTESTPATH}/libgtest_main.a pthread)
#add_test( ${TESTNAME} ${TESTNAME} )
