cmake_minimum_required(VERSION 3.14)
project(passivedns)

set(CMAKE_CXX_STANDARD 14)
include(FindPCAP.cmake)
find_library(TINS_LIBRARY tins)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h)
add_executable(passivedns ${SOURCE_FILES})

target_link_libraries(passivedns "${TINS_LIBRARY}")