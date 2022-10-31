cmake_minimum_required(VERSION 3.21)
project(pyvm)

set(CMAKE_CXX_STANDARD 11)

add_executable(pyvm main.cpp
        object/pyObject.cpp
        object/pyInteger.cpp
        object/pyString.cpp
        object/functionObject.cpp
        util/arrayList.cpp
        util/map.cpp
        code/binaryFileParser.cpp
        code/codeObject.cpp
        runtime/interpreter.cpp
        runtime/universe.cpp
        runtime/frameObject.cpp)

INCLUDE_DIRECTORIES(./)