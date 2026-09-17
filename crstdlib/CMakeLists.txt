cmake_minimum_required(VERSION 3.31)

project(CrushaStdLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

file(GLOB SRC_FILES "src/*.cppm")

add_library(crstdlib SHARED)
target_sources(crstdlib PUBLIC FILE_SET modules_public TYPE CXX_MODULES FILES ${SRC_FILES})
