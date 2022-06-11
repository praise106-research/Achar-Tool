cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(achar_rq2_example)
set (CMAKE_CXX_STANDARD 17)
include_directories(include)

add_executable ($ENV{RUNNER} src/$ENV{RUNNER}.c)
set_property(TARGET $ENV{RUNNER} PROPERTY CXX_STANDARD 17)