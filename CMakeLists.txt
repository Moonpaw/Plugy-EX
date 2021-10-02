cmake_minimum_required(VERSION 3.20)

project(PlugY_fork)

# Prepare doctest for other targets to use
find_package(doctest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

include_directories(Commons)
include_directories(PlugY)
#
#add_library(Commons STATIC
#        Commons/d2BinFile.h
#        Commons/d2constants.h
#        Commons/d2StringTblStruct.h
#        Commons/d2Struct.h
#        Commons/D2UnitStruct.h
#        Commons/updatingConst.h
#        Commons/VersionInfo.cpp
#        Commons/VersionInfo.h)
add_subdirectory(Commons)
add_subdirectory(PlugY)
add_subdirectory(PlugY.Tests)

#add_custom_command(TARGET PlugY
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PlugY> "C:/Games/Diablo II - D2SE/MODS/Zy El by Moonpaw")