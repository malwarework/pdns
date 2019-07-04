include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

cmake_minimum_required(VERSION 3.9.2)
project(passivedns)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lz -lssl -lcrypt -lcppkafka -lrdkafka++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lz -lssl -lcrypt -lrdkafka++")

set( BUILD_DIR ${CMAKE_BINARY_DIR}/build)
set( SRC_DIR ${CMAKE_BINARY_DIR}/src)

set(Boost_DEBUG 1)

set( boost_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/src/boost )
set( boost_INCLUDE_DIR ${boost_INSTALL}/include )
set( boost_LIB_DIR ${boost_INSTALL}/lib )
message(${boost_INSTALL})

set( librdkafka_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/src/librdkafka )
set( librdkafka_INCLUDE_DIR ${librdkafka_INSTALL}/include )
set( librdkafka_LIB_DIR ${librdkafka_INSTALL}/lib )
message(${librdkafka_INSTALL})

set( json_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/src/json )
set( json_INCLUDE_DIR ${json_INSTALL}/include )
set( json_LIB_DIR ${json_INSTALL}/lib )
message(${json_INSTALL})

set( libtins_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/src/libtins )
set( libtins_INCLUDE_DIR ${libtins_INSTALL}/include )
set( libtins_LIB_DIR ${libtins_INSTALL}/lib )
message(${libtins_INSTALL})

set( cppkafka_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/src/cppkafka )
set( cppkafka_INCLUDE_DIR ${cppkafka_INSTALL}/include )
set( cppkafka_LIB_DIR ${cppkafka_INSTALL}/lib )
message(${cppkafka_INSTALL})


include(CMakeListsExternal.txt)


find_package(nlohmann_json 3.2.0 REQUIRED)
find_library(OPTIONS_LIBRARY
		boost_program_options
		PATHS ${boost_LIB_DIR}
		NO_DEFAULT_PATH)
find_library(RDKAFKA_LIBRARY
		rdkafka++
		PATHS ${librdkafka_LIB_DIR}
		NO_DEFAULT_PATH)
find_library(CPPKAFKA_LIBRARY
		cppkafka
		PATHS ${cppkafka_LIB_DIR}
		NO_DEFAULT_PATH)
find_library(TINS_LIBRARY
		tins
		${libtins_LIB_DIR}
		NO_DEFAULT_PATH)
#message(${RDKAFKA_LIBRARY})
#message(${CPPKAFKA_LIBRARY})
#message(${TINS_LIBRARY})

set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h KafkaConnector.cpp KafkaConnector.h)
add_executable(passivedns ${SOURCE_FILES})

add_dependencies(passivedns boost librdkafka json libtins cppkafka)

target_include_directories(passivedns PUBLIC ${boost_INCLUDE_DIR} ${librdkafka_INCLUDE_DIR} ${json_INCLUDE_DIR} ${libtins_INCLUDE_DIR} ${cppkafka_INCLUDE_DIR})
target_link_libraries(passivedns "${TINS_LIBRARY}" "${RDKAFKA_LIBRARY}" "${CPPKAFKA_LIBRARY}" ${OPTIONS_LIBRARY})