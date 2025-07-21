cmake_minimum_required(VERSION 3.20)

project(Dependencies)

include(FetchContent)

FetchContent_Declare(
  ArgsParser
  GIT_REPOSITORY "https://github.com/NikitaZhinov/ArgsParser"
  GIT_TAG v2.0.1
)
FetchContent_MakeAvailable(ArgsParser)

FetchContent_Declare(
  UniversalLexer
  GIT_REPOSITORY "https://github.com/NikitaZhinov/UniversalLexer"
  GIT_TAG v1.1.1
)
FetchContent_MakeAvailable(UniversalLexer)
