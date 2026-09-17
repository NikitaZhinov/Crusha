cmake_minimum_required(VERSION 3.31)

project(CrushaDependencies)

if (WIN32)
	include(FetchContent)
    FetchContent_Declare(winflexbison
        URL https://github.com/lexxmark/winflexbison/releases/download/v2.5.25/win_flex_bison-2.5.25.zip)
    FetchContent_MakeAvailable(winflexbison)
    set(FLEX_EXECUTABLE "${winflexbison_SOURCE_DIR}/win_flex.exe" CACHE FILEPATH "" FORCE)
    set(BISON_EXECUTABLE "${winflexbison_SOURCE_DIR}/win_bison.exe" CACHE FILEPATH "" FORCE)
    set(WinFlexBisonSourseDir ${winflexbison_SOURCE_DIR} CACHE FILEPATH "" FORCE)
endif()

add_subdirectory("options")
