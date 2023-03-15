cmake_minimum_required(VERSION 3.14)
project(S21Matrix)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/b796f7d44681514f58a683a3a71ff17c94edb0c1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  s21matrix_test
  src/s21_matrix_oop.cpp
  src/test.cpp
)
target_link_libraries(
  s21matrix_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(s21matrix_test)
