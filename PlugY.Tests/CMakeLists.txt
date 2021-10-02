cmake_minimum_required(VERSION 3.20)

project(PlugY.Tests)

# Prepare doctest for other targets to use
find_package(doctest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
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


add_executable(PlugY.Tests initTests.cpp)
target_compile_features(PlugY.Tests PRIVATE cxx_std_17)
target_link_libraries(PlugY.Tests
        PRIVATE doctest::doctest
        PRIVATE PlugY)
#target_link_libraries(PlugY.Tests PRIVATE Commons)

#add_custom_command(TARGET PlugY
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PlugY> "C:/Games/Diablo II - D2SE/MODS/Zy El by Moonpaw")