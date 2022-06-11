cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(achar_Opaque_example)
set (CMAKE_CXX_STANDARD 17)

find_package(Torch REQUIRED)
include_directories(include)

add_executable ($ENV{RUNNER} src/$ENV{RUNNER}.cpp)
target_link_libraries($ENV{RUNNER} "${TORCH_LIBRARIES}")
set_property(TARGET $ENV{RUNNER} PROPERTY CXX_STANDARD 17)