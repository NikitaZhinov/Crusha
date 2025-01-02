cmake_minimum_required(VERSION 3.20)

project(CRC VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

if (WIN32)
	set(CMAKE_CXX_FLAGS "/EHsc /DCRC_VERSION=\\\"${PROJECT_VERSION}\\\"")
	set(CMAKE_CXX_FLAGS_DEBUG "/Z7 /Zi /ZI /DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else()
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -DCRC_VERSION=\\\"${PROJECT_VERSION}\\\"")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

add_executable(${PROJECT_NAME} "src/main.cpp" "include/args-parser/args-parser.h" "src/args-parser/args-parser.cpp"   "include/args-parser/option.h" "src/args-parser/option.cpp" "include/args-parser/option-list.h" "src/args-parser/option-list.cpp" "include/lexer/lexer.h" "src/lexer/lexer.cpp"    )
