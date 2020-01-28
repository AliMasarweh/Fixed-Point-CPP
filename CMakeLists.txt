cmake_minimum_required(VERSION 3.15)
project(FixedPointPrice)

set(CMAKE_CXX_STANDARD 98)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(FixedPointPriceTest test_price.cpp price.h)
target_link_libraries(FixedPointPriceTest gtest gtest_main pthread)

