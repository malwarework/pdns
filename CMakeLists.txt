include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

cmake_minimum_required(VERSION 3.9.2)
project(passivedns)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lz -lssl -lcrypt -lcppkafka -lrdkafka++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lz -lssl -lcrypt")

set(Boost_DEBUG 1)

set( boost_INSTALL ${PROJECT_SOURCE_DIR}/lib/boost )
set( boost_INCLUDE_DIR ${boost_INSTALL}/include )
set( boost_LIB_DIR ${boost_INSTALL}/lib )

set( librdkafka_INSTALL ${PROJECT_SOURCE_DIR}/lib/librdkafka )
set( librdkafka_INCLUDE_DIR ${librdkafka_INSTALL}/include )
set( librdkafka_LIB_DIR ${librdkafka_INSTALL}/lib )

set( json_INSTALL ${PROJECT_SOURCE_DIR}/src/json )
set( json_INCLUDE_DIR ${json_INSTALL}/include )
set( json_LIB_DIR ${json_INSTALL}/lib )

set( libtins_INSTALL ${PROJECT_SOURCE_DIR}/lib/libtins )
set( libtins_INCLUDE_DIR ${libtins_INSTALL}/include )
set( libtins_LIB_DIR ${libtins_INSTALL}/lib )

set( cppkafka_INSTALL ${PROJECT_SOURCE_DIR}/lib/cppkafka )
set( cppkafka_INCLUDE_DIR ${cppkafka_INSTALL}/include )
set( cppkafka_LIB_DIR ${cppkafka_INSTALL}/lib )

set(JSON_BuildTests OFF CACHE INTERNAL "")

include_directories(src include)
add_subdirectory(lib/nlohmann_json)

#
include(ExternalProject)
#boost
externalproject_add(boost
		BUILD_IN_SOURCE		1
		PREFIX			boost
		URL			https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz
		TLS_VERIFY		0
		CONFIGURE_COMMAND	./bootstrap.sh --prefix=<INSTALL_DIR>
		UPDATE_COMMAND		""
		BUILD_COMMAND		./b2 install
		INSTALL_COMMAND		""
		INSTALL_DIR		${boost_INSTALL}
		)
externalproject_add_steptargets(boost build install)

# LibrdKafka
externalproject_add(librdkafka
		BUILD_IN_SOURCE         1
		DEPENDS					boost
		PREFIX					librdkafka
		GIT_REPOSITORY			https://github.com/edenhill/librdkafka.git
		CONFIGURE_COMMAND		./configure --prefix=<INSTALL_DIR> --enable-static
		INSTALL_DIR				${librdkafka_INSTALL}
		)
externalproject_add_steptargets(librdkafka build install)

#JSON
externalproject_add(json
		BUILD_IN_SOURCE         1
		DEPENDS                 boost
		PREFIX                  json
		GIT_REPOSITORY          https://github.com/nlohmann/json.git
		CMAKE_ARGS              -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
		INSTALL_DIR             ${json_INSTALL}
		)
externalproject_add_steptargets(json build install)

#Libtins
externalproject_add(libtins
		BUILD_IN_SOURCE         1
		DEPENDS                 boost
		PREFIX                  libtins
		GIT_REPOSITORY          https://github.com/mfontanini/libtins.git
		CMAKE_ARGS              -DLIBTINS_ENABLE_CXX11=1 -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DLIBTINS_BUILD_SHARED=0
		INSTALL_DIR             ${libtins_INSTALL}
		)
externalproject_add_steptargets(libtins build install)

#CPPKafka
externalproject_add(cppkafka
		BUILD_IN_SOURCE         1
		DEPENDS                 librdkafka
		PREFIX                  cppkafka
		GIT_REPOSITORY          https://github.com/mfontanini/cppkafka.git
		CMAKE_ARGS              -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DBOOST_ROOT=${boost_INSTALL} -DCPPKAFKA_RDKAFKA_STATIC_LIB=ON -DCPPKAFKA_BUILD_SHARED=OFF
		INSTALL_DIR             ${cppkafka_INSTALL}
		)
externalproject_add_steptargets(cppkafka build install)


#find_package(nlohmann_json 3.2.0 REQUIRED)

find_library(OPTIONS_LIBRARY
		boost_program_options
		PATHS ${boost_LIB_DIR}
		NO_DEFAULT_PATH)
if (NOT OPTIONS_LIBRARY)
	message("Cant find OPTIONS_LIBRARY")
endif ()

find_library(RDKAFKA_LIBRARY
		rdkafka++
		PATHS ${librdkafka_LIB_DIR}
		NO_DEFAULT_PATH)
if (NOT RDKAFKA_LIBRARY)
	message("Cant find RDKAFKA_LIBRARY")
endif ()

find_library(CPPKAFKA_LIBRARY
		cppkafka
		PATHS ${cppkafka_LIB_DIR}
		NO_DEFAULT_PATH)
if (NOT CPPKAFKA_LIBRARY)
	message("Cant find CPPKAFKA_LIBRARY")
endif ()

find_library(TINS_LIBRARY
		tins
		${libtins_LIB_DIR}
		NO_DEFAULT_PATH)
if (NOT TINS_LIBRARY)
	message("Cant find TINS_LIBRARY")
endif ()
message(${RDKAFKA_LIBRARY})
message(${CPPKAFKA_LIBRARY})
message(${TINS_LIBRARY})

set(SOURCE_FILES src/main.cpp src/TrafficeVolumeReduction.cpp include/TrafficeVolumeReduction.h include/config.h src/PeriodicListPrunning.cpp include/PeriodicListPrunning.h src/KafkaConnector.cpp include/KafkaConnector.h)
add_executable(passivedns ${SOURCE_FILES})

add_dependencies(passivedns boost librdkafka json libtins cppkafka)

target_include_directories(passivedns PRIVATE ${boost_INCLUDE_DIR} ${librdkafka_INCLUDE_DIR} ${json_INCLUDE_DIR} ${libtins_INCLUDE_DIR} ${cppkafka_INCLUDE_DIR})
target_link_libraries(passivedns "${TINS_LIBRARY}" "${RDKAFKA_LIBRARY}" "${CPPKAFKA_LIBRARY}" ${OPTIONS_LIBRARY} nlohmann_json::nlohmann_json)

install(TARGETS passivedns RUNTIME DESTINATION bin PERMISSIONS WORLD_EXECUTE)
install(FILES passivedns.conf PERMISSIONS WORLD_EXECUTE TYPE SYSCONF)