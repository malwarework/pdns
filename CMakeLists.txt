cmake_minimum_required(VERSION 3.14)
project(passivedns)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lcppkafka -lrdkafa")
find_library(TINS_LIBRARY tins)
find_library(RDKAFKA_LIBRARY rdkafka)
find_library(CPPKAFKA_LIBRARY cppkafka)
find_package(nlohmann_json 3.2.0 REQUIRED)

#set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h KafkaConnector.cpp KafkaConnector.h)
set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h)
add_executable(passivedns ${SOURCE_FILES})

target_link_libraries(passivedns "${TINS_LIBRARY}" "${RDKAFKA_LIBRARY}" "${CPPKAFKA_LIBRARY}")