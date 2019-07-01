cmake_minimum_required(VERSION 3.14)
project(passivedns)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lcppkafka -lrdkafka")
find_library(TINS_LIBRARY tins)
include_directories("/usr/include/librdkafka")
include_directories("/usr/include/cppkafka")
FIND_LIBRARY(RDKAFKA rdkafka /usr/lib NO_DEFAULT_PATH)
FIND_LIBRARY(CPPKAFKA cppkafka /usr/lib NO_DEFAULT_PATH)
find_package(nlohmann_json 3.2.0 REQUIRED)
link_libraries(${RDKAFKA} ${CPPKAFKA})

#set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h KafkaConnector.cpp KafkaConnector.h)
set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h)
add_executable(passivedns ${SOURCE_FILES})

target_link_libraries(passivedns "${TINS_LIBRARY}" cppkafka rdkafka)