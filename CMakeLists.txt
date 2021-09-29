cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE STRING "Default CXX options" FORCE)
set(CMAKE_C_FLAGS /MP)


project(PlugY_fork)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

include_directories(Commons)
include_directories(PlugY)

add_library(PlugY SHARED
        Commons/d2BinFile.h
        Commons/d2constants.h
        Commons/d2StringTblStruct.h
        Commons/d2Struct.h
        Commons/D2UnitStruct.h
        Commons/updatingConst.h
        Commons/VersionInfo.cpp
        Commons/VersionInfo.h
        PlugY/PCXFiles/EmptyPage.pcx
        PlugY/PCXFiles/SharedGoldBtns.pcx
        PlugY/PCXFiles/StashBtns.pcx
        PlugY/PCXFiles/StatsBackground.pcx
        PlugY/PCXFiles/TradeStash.pcx
        PlugY/PCXFiles/UnassignSkillsBtns.pcx
        PlugY/PCXFiles/UnassignStatsBtns.pcx
        PlugY/BigStash.cpp
        PlugY/bigStash.h
        PlugY/ClientSaveFile.cpp
        PlugY/clientSaveFile.h
        PlugY/Commands.cpp
        PlugY/commands.h
        PlugY/Common.cpp
        PlugY/common.h
        PlugY/customData.h
        PlugY/CustomLibraries.cpp
        PlugY/customLibraries.h
        PlugY/D2functions.cpp
        PlugY/d2functions.h
        PlugY/D2wrapper.cpp
        PlugY/d2wrapper.h
        PlugY/Error.cpp
        PlugY/error.h
        PlugY/ExtendedSaveFile.cpp
        PlugY/extendedSaveFile.h
        PlugY/ExtraOptions.cpp
        PlugY/extraOptions.h
        PlugY/GlobalVariable.cpp
        PlugY/globalVariable.h
        PlugY/InfinityStash.cpp
        PlugY/infinityStash.h
        PlugY/INIfile.cpp
        PlugY/INIfile.h
        PlugY/Interface_Skills.cpp
        PlugY/interface_Skills.h
        PlugY/Interface_Stash.cpp
        PlugY/interface_Stash.h
        PlugY/Interface_Stats.cpp
        PlugY/interface_Stats.h
        PlugY/Language.cpp
        PlugY/language.h
        PlugY/LoadPlayerData.cpp
        PlugY/loadPlayerData.h
        PlugY/LocalizedStrings.cpp
        PlugY/LocalizedStrings.h
        PlugY/MainScreen.cpp
        PlugY/mainScreen.h
        PlugY/ModifMemory.cpp
        PlugY/modifMemory.h
        PlugY/NewInterface_CubeListing.cpp
        PlugY/newInterface_CubeListing.h
        PlugY/NewInterface_Runewords.cpp
        PlugY/newInterface_Runewords.h
        PlugY/NewInterface_Stats.cpp
        PlugY/newInterface_Stats.h
        PlugY/NewInterface_StatsPageTwo.cpp
        PlugY/newInterface_StatsPageTwo.h
        PlugY/NewInterfaces.cpp
        PlugY/newInterfaces.h
        PlugY/OthersFeatures.cpp
        PlugY/othersFeatures.h
        PlugY/Parameters.cpp
        PlugY/parameters.h
        PlugY/PlayerCustomData.cpp
        PlugY/playerCustomData.h
        PlugY/PlugY.cpp
        PlugY/PlugYFiles.cpp
        PlugY/plugYFiles.h
        PlugY/resource.h
        PlugY/SavePath.cpp
        PlugY/savePath.h
        PlugY/SavePlayerData.cpp
        PlugY/savePlayerData.h
        PlugY/SharedSaveFile.cpp
        PlugY/sharedSaveFile.h
        PlugY/SkillPerLevelUp.cpp
        PlugY/skillPerLevelUp.h
        PlugY/SkillsPoints.cpp
        PlugY/skillsPoints.h
        PlugY/StatPerLevelUp.cpp
        PlugY/statPerLevelUp.h
        PlugY/StatsPoints.cpp
        PlugY/statsPoints.h
        PlugY/targetver.h
        PlugY/UberQuest.cpp
        PlugY/uberQuest.h
        PlugY/UpdateClient.cpp
        PlugY/updateClient.h
        PlugY/UpdateServer.cpp
        PlugY/updateServer.h
        PlugY/Windowed.cpp
        PlugY/windowed.h
        PlugY/WorldEvent.cpp
        PlugY/worldEvent.h)

add_custom_command(TARGET PlugY
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PlugY> "C:/Games/Diablo II - D2SE/MODS/Zy El by Moonpaw")