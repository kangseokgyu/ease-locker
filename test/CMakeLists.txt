add_executable(
  guard_test
  guard_test.cpp
)

target_include_directories(
  guard_test
PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
  guard_test
  GTest::gtest_main
  locker
)

include(GoogleTest)
gtest_discover_tests(guard_test)
