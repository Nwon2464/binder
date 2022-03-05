cmake_minimum_required(VERSION 3.20.2 FATAL_ERROR)
project(cf CXX)
add_executable(cf a.cpp b.cpp)
target_compile_features(cf PRIVATE cxx_range_for)

