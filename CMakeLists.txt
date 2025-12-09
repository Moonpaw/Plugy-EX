cmake_minimum_required(VERSION 3.20)

project (Commons VERSION 1.0.0)
include(CMakePrintHelpers)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Add a library with the above sources
add_library(${PROJECT_NAME} STATIC Commons/src/VersionInfo.cpp)
add_library(PlugY::Commons ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/include
        PRIVATE
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/src
        )
cmake_print_properties(
        TARGETS Commons PROPERTIES
        POSITION_INDEPENDENT_CODE INTERFACE_INCLUDE_DIRECTORIES
)

add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "C:/Games/Diablo II - D2SE/MODS/Zy El by Moonpaw")

###############################################################################
project(PlugY VERSION 0.0.1)
include(CMakePrintHelpers)

find_package(nameof REQUIRED)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
cmake_print_variables(PROJECT_NAME)

set(PlugYSources
        PlugY/src/BigStash.cpp
        PlugY/src/Commands.cpp
        PlugY/src/Common.cpp
        PlugY/src/CustomLibraries.cpp
        PlugY/src/D2functions.cpp
        PlugY/src/D2wrapper.cpp
        PlugY/src/Error.cpp
        PlugY/src/ExtendedSaveFile.cpp
        PlugY/src/ExtraOptions.cpp
        PlugY/src/GlobalVariable.cpp
        PlugY/src/InfinityStash.cpp
        PlugY/src/INIfile.cpp
        PlugY/src/Interface_Skills.cpp
        PlugY/src/Interface_Stash.cpp
        PlugY/src/Interface_Stats.cpp
        PlugY/src/Language.cpp
        PlugY/src/LoadPlayerData.cpp
        PlugY/src/LocalizedStrings.cpp
        PlugY/src/MainScreen.cpp
        PlugY/src/ModifMemory.cpp
        PlugY/src/NewInterface_CubeListing.cpp
        PlugY/src/NewInterface_Runewords.cpp
        PlugY/src/NewInterface_Stats.cpp
        PlugY/src/NewInterface_StatsPageTwo.cpp
        PlugY/src/NewInterfaces.cpp
        PlugY/src/Parameters.cpp
        PlugY/src/PlayerCustomData.cpp
        PlugY/src/PlugY.cpp
        PlugY/src/PlugYFiles.cpp
        PlugY/src/SavePath.cpp
        PlugY/src/SavePlayerData.cpp
        PlugY/src/SharedSaveFile.cpp
        PlugY/src/SkillPerLevelUp.cpp
        PlugY/src/SkillsPoints.cpp
        PlugY/src/StatPerLevelUp.cpp
        PlugY/src/StatsPoints.cpp
        PlugY/src/UberQuest.cpp
        PlugY/src/UpdateClient.cpp
        PlugY/src/UpdateServer.cpp
        PlugY/src/Windowed.cpp
        PlugY/src/WorldEvent.cpp)
add_library(${PROJECT_NAME} SHARED ${PlugYSources})

add_library(PlugY::PlugY ALIAS ${PROJECT_NAME})

add_library(${PROJECT_NAME}Static STATIC ${PlugYSources})

add_library(PlugY::PlugYStatic ALIAS ${PROJECT_NAME}Static)

target_include_directories( ${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/include
        PRIVATE
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/src
        )
target_include_directories( ${PROJECT_NAME}Static
        PUBLIC
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/include
        PRIVATE
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/src
        )

cmake_print_properties(
        TARGETS PlugY
        PROPERTIES POSITION_INDEPENDENT_CODE
)

target_link_libraries(${PROJECT_NAME}
        Commons
        nameof::nameof)
target_link_libraries(${PROJECT_NAME}Static
        Commons
        nameof::nameof)

add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "C:/Games/Diablo II - D2SE/MODS/Zy El by Moonpaw")

###############################################################################
project(PlugY_Tests)
include(CMakePrintHelpers)
# Prepare doctest for other targets to use
find_package(doctest REQUIRED)


add_executable(PlugY_Tests  PlugY.Tests/initTests.cpp)
target_compile_features(PlugY_Tests PRIVATE cxx_std_17)
target_link_libraries(PlugY_Tests
        PRIVATE
        doctest::doctest
        PlugY::PlugYStatic)

