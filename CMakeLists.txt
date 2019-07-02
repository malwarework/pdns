include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

cmake_minimum_required(VERSION 3.14)
project(passivedns)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lcppkafka -lrdkafka++")

set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h KafkaConnector.cpp KafkaConnector.h)
add_executable(passivedns ${SOURCE_FILES})

include(ExternalProject)

externalproject_add(boost
        GIT_REPOSITORY			https://github.com/boostorg/boost.git
        GIT_TAG                 master
        SOURCE_DIR              "${CMAKE_BINARY_DIR}/boost-src"
        BINARY_DIR              "${CMAKE_BINARY_DIR}/boost-build"
	CMAKE_COMMAND		"./bootstrap.sh"
	BUILD_COMMAND		"./b2"
	INSTALL_COMMAND		"./b2 install"
)
externalproject_add_steptargets(boost build install)

externalproject_add(json
	GIT_REPOSITORY		https://github.com/nlohmann/json.git
	GIT_TAG			master
	SOURCE_DIR		"${CMAKE_BINARY_DIR}/json-src"
	BINARY_DIR		"${CMAKE_BINARY_DIR}/json-build"
)
externalproject_add_steptargets(json build install)

externalproject_add(libtins
        GIT_REPOSITORY          https://github.com/mfontanini/libtins.git
        GIT_TAG                 master
        SOURCE_DIR              "${CMAKE_BINARY_DIR}/libtins-src"
        BINARY_DIR              "${CMAKE_BINARY_DIR}/libtins-build"
	CMAKE_ARGS		"-DLIBTINS_ENABLE_CXX11=1"
)
externalproject_add_steptargets(libtins build install)

add_dependencies(passivedns boost json libtins)

find_library(TINS_LIBRARY tins)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_library(RDKAFKA_LIBRARY rdkafka++)
find_library(CPPKAFKA_LIBRARY cppkafka)
message(${CPPKAFKA_LIBRARY})
#set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h KafkaConnector.cpp KafkaConnector.h)
#add_executable(passivedns ${SOURCE_FILES})
##target_link_libraries(passivedns "${TINS_LIBRARY}" "/usr/local/lib/librdkafka.so" "/usr/local/lib64/libcppkafka.so")
#target_link_libraries(passivedns "${TINS_LIBRARY}" "${RDKAFKA_LIBRARY}" "/usr/local/lib64/libcppkafka.so")
