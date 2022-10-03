cmake_minimum_required(VERSION 3.21)
project(pyvm)

set(CMAKE_CXX_STANDARD 11)

add_executable(pyvm main.cpp
        object/pyInteger.cpp
        object/pyString.cpp
        util/arrayList.cpp
        code/binaryFileParser.cpp
        code/codeObject.cpp)

INCLUDE_DIRECTORIES(./)