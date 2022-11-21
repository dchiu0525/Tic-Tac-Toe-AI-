cmake_minimum_required(VERSION 3.5)
project(FINAL CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(XO_SOURCE
  XO.hpp XO.cpp)

set(BOARDXO_SOURCE
  BoardXO.hpp)

# create unittests
set(SOURCE ${XO_SOURCE} ${BOARDXO_SOURCE})

# create unittests
add_executable(student-tests catch.hpp student_catch.cpp ${SOURCE} student_tests.cpp)
# some simple tests
enable_testing()
add_test(student-tests student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  XO.hpp XO.cpp BoardXO.hpp student_tests.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
