cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(binary_search_test CXX)

enable_testing()

find_package(GTest MODULE REQUIRED)

add_executable(binary_search_test "binary_search_test.cpp")

target_link_libraries(binary_search_test GTest::GTest GTest::Main)

add_test(BinarySearchTest binary_search_test)
