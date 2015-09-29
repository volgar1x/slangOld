cmake_minimum_required(VERSION 3.3)
project(slang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

include_directories(slang include)
set(SOURCE_FILES src/main.cpp src/slang/Lexer.cpp src/slang/Parser.cpp)
add_executable(slang ${SOURCE_FILES})