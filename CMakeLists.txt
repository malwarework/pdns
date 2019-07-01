cmake_minimum_required(VERSION 3.14)
project(passivedns)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lcppkafka -lrdkafka++")
find_library(TINS_LIBRARY tins)
FIND_LIBRARY(RDKAFKA_LIBRARY rdkafka++)
find_package(nlohmann_json 3.2.0 REQUIRED)

#set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h KafkaConnector.cpp KafkaConnector.h)
set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h)
add_executable(passivedns ${SOURCE_FILES})

#target_link_libraries(passivedns "${TINS_LIBRARY}" "${RDKAFKA_LIBRARY}" "/usr/local/lib64/libcppkafka.so")
target_link_libraries(passivedns "${TINS_LIBRARY}")