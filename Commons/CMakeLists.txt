cmake_minimum_required(VERSION 3.20)

project(Commons VERSION 1.2.3)


include_directories(includes)

add_library(Commons SHARED
        src/VersionInfo.cpp)

#add_library(JSONUtils::jsonutils ALIAS jsonutils)

target_include_directories(Commons
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(Commons PRIVATE cxx_std_17)

##############################################
# Installation instructions
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Commons)

install(TARGETS Commons
        EXPORT Commons-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT Commons-targets
    FILE
        CommonsTargets.cmake
    NAMESPACE
        Commons::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/CommonsConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/CommonsConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/CommonsConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
        )

#Install the config, configversion and custom find modules
install(FILES
        ${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JSONUtilsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JSONUtilsConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
        )

##############################################
## Exporting from the build tree
export(EXPORT Commons-targets
        FILE ${CMAKE_CURRENT_BINARY_DIR}/CommonsTargets.cmake
        NAMESPACE Commons::)

#Register package in the User Package Registry
export(PACKAGE Commons)

##############################################
## Add test
#enable_testing()
#add_subdirectory(test)