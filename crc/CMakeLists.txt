cmake_minimum_required(VERSION 3.30)

project(CRC VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_definitions(CRC_VERSION=\"${PROJECT_VERSION}\")
if (CMAKE_BUILD_TYPE STREQUAL Release)
    if (WIN32)
        add_compile_options(/O2)
    else()
        add_compile_options(-Wall -Wextra)
        add_compile_options(-O3)
    endif()
else()
    add_compile_definitions(DEBUG)
    if (NOT WIN32)
        add_compile_options(-Wall -Wextra)
    endif()
endif()

add_executable(${PROJECT_NAME} "src/main.cpp" "include/option/default.h" "src/default.cpp"
                               "include/compiler/compiler.h" "src/compiler.cpp"
                               "include/compiler/parser.h" "include/compiler/dictionary.h"
                               "src/dictionary.cpp" "include/compiler/ast.h" "include/option/version.h" "include/option/option.h" "src/version.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE ArgsParser PRIVATE UniversalLexer)
target_include_directories(${PROJECT_NAME} PRIVATE "${ArgsParser_SOURCE_DIR}/include"
                                           PRIVATE "${UniversalLexer_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "include")
