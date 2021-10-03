cmake_minimum_required(VERSION 3.20)

project(PlugY)

# Prepare doctest for other targets to use
find_package(Commons REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

add_library(PlugY SHARED
        PCXFiles/EmptyPage.pcx
        PCXFiles/SharedGoldBtns.pcx
        PCXFiles/StashBtns.pcx
        PCXFiles/StatsBackground.pcx
        PCXFiles/TradeStash.pcx
        PCXFiles/UnassignSkillsBtns.pcx
        PCXFiles/UnassignStatsBtns.pcx
        interface_Skills.h
        Interface_Stash.cpp
        interface_Stash.h
        Interface_Stats.cpp
        interface_Stats.h
        Language.cpp
        language.h
        LoadPlayerData.cpp
        loadPlayerData.h
        LocalizedStrings.cpp
        LocalizedStrings.h
        modifMemory.h
        NewInterface_CubeListing.cpp
        newInterface_CubeListing.h
        NewInterface_Runewords.cpp
        newInterface_Runewords.h
        NewInterface_Stats.cpp
        newInterface_Stats.h
        NewInterface_StatsPageTwo.cpp
        newInterface_StatsPageTwo.h
        savePath.h
        SavePlayerData.cpp
        savePlayerData.h
        SharedSaveFile.cpp
        sharedSaveFile.h
        SkillPerLevelUp.cpp
        skillPerLevelUp.h
        SkillsPoints.cpp
        skillsPoints.h
        StatPerLevelUp.cpp
        statPerLevelUp.h
        StatsPoints.cpp
        statsPoints.h
        targetver.h
        UberQuest.cpp
        uberQuest.h
        updateServer.h
        Windowed.cpp
        windowed.h
        WorldEvent.cpp
        worldEvent.h)
target_link_libraries(PlugY PRIVATE Commons)