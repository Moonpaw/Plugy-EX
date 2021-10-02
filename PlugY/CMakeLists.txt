cmake_minimum_required(VERSION 3.20)

project(PlugY)

# Prepare doctest for other targets to use
find_package(Commons REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

add_library(PlugY SHARED
        D2TypeDefMacros.h
        D2TypeNameMacros.h
        PCXFiles/EmptyPage.pcx
        PCXFiles/SharedGoldBtns.pcx
        PCXFiles/StashBtns.pcx
        PCXFiles/StatsBackground.pcx
        PCXFiles/TradeStash.pcx
        PCXFiles/UnassignSkillsBtns.pcx
        PCXFiles/UnassignStatsBtns.pcx
        BigStash.cpp
        bigStash.h
        Commands.cpp
        commands.h
        Common.cpp
        common.h
        CustomLibraries.cpp
        customLibraries.h
        D2functions.cpp
        d2functions.h
        D2wrapper.cpp
        d2wrapper.h
        Error.cpp
        error.h
        ExtendedSaveFile.cpp
        extendedSaveFile.h
        ExtraOptions.cpp
        extraOptions.h
        GlobalVariable.cpp
        globalVariable.h
        InfinityStash.cpp
        infinityStash.h
        INIfile.cpp
        INIfile.h
        Interface_Skills.cpp
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
        MainScreen.cpp
        mainScreen.h
        ModifMemory.cpp
        modifMemory.h
        NewInterface_CubeListing.cpp
        newInterface_CubeListing.h
        NewInterface_Runewords.cpp
        newInterface_Runewords.h
        NewInterface_Stats.cpp
        newInterface_Stats.h
        NewInterface_StatsPageTwo.cpp
        newInterface_StatsPageTwo.h
        NewInterfaces.cpp
        newInterfaces.h
        Parameters.cpp
        parameters.h
        PlayerCustomData.cpp
        playerCustomData.h
        PlugY.cpp
        PlugYFiles.cpp
        plugYFiles.h
        resource.h
        SavePath.cpp
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
        UpdateClient.cpp
        updateClient.h
        UpdateServer.cpp
        updateServer.h
        Windowed.cpp
        windowed.h
        WorldEvent.cpp
        worldEvent.h)
target_link_libraries(PlugY PRIVATE Commons)