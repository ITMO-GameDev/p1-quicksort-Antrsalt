cmake_minimum_required(VERSION 3.15)
project(P3Dictionary)

set(CMAKE_CXX_STANDARD 14)

add_executable(P3Dictionary Dictionary.cpp Dictionary.h Node.h DictionaryTest.cpp)