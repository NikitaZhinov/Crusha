cmake_minimum_required(VERSION 3.20)

project(CRC VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if (WIN32)
	set(CMAKE_CXX_FLAGS "/DCRC_VERSION=\\\"${PROJECT_VERSION}\\\"")
	set(CMAKE_CXX_FLAGS_DEBUG "/DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else()
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -DCRC_VERSION=\\\"${PROJECT_VERSION}\\\"")
	set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

add_executable(${PROJECT_NAME} "src/main.cpp" "include/args-parser/args-parser.h" "src/args-parser/args-parser.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE "include")
