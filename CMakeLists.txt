include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

cmake_minimum_required(VERSION 3.14)
project(passivedns)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lz -lssl -lcrypt -lcppkafka -lrdkafka++")
set( Boost_Bootstrap_Command ./bootstrap.sh )
set( Boost_b2_Command ./b2 )
set( Boost_INCLUDE_DIR ${INSTALL_DEPENDENCIES_DIR}/include )
set( Boost_LIBRARY_DIR ${INSTALL_DEPENDENCIES_DIR}/lib )
set( BUILD_DIR ${CMAKE_BINARY_DIR}/build)
set( SRC_DIR ${CMAKE_BINARY_DIR}/src)



find_package(nlohmann_json 3.2.0 REQUIRED)
find_library(RDKAFKA_LIBRARY
		rdkafka++
		PATHS ${BUILD_DIR}
		NO_DEFAULT_PATH)
find_library(CPPKAFKA_LIBRARY
		cppkafka
		PATHS ${BUILD_DIR}/cppkafka/lib
		NO_DEFAULT_PATH)
find_library(TINS_LIBRARY
		tins
		${BUILD_DIR}/libtins/lib
		NO_DEFAULT_PATH)

message(${RDKAFKA_LIBRARY})
message(${CPPKAFKA_LIBRARY})
message(${TINS_LIBRARY})

set(SOURCE_FILES main.cpp TrafficeVolumeReduction.cpp TrafficeVolumeReduction.h config.h PeriodicListPrunning.cpp PeriodicListPrunning.h KafkaConnector.cpp KafkaConnector.h)
add_executable(passivedns ${SOURCE_FILES})


if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(Boost_address_model 64)
else()
	set(Boost_address_model 32)
endif()

if(${BUILD_SHARED_LIBS} MATCHES OFF)
	set(BUILD_LIBS "static")
elseif(${BUILD_SHARED_LIBS} MATCHES ON)
	set(BUILD_LIBS "shared")
endif()

include(ExternalProject)

#Boost
#externalproject_add(boost
#		GIT_REPOSITORY			https://github.com/boostorg/boost.git
#        GIT_TAG                 master
#        SOURCE_DIR              "${CMAKE_BINARY_DIR}/build/boost-src"
##        BINARY_DIR              "${CMAKE_BINARY_DIR}/build/boost-build"
#		UPDATE_COMMAND 			""
#		CONFIGURE_COMMAND 		"${Boost_Bootstrap_Command}"
#		BUILD_COMMAND 			${Boost_b2_Command} install -j8   --prefix=${INSTALL_DEPENDENCIES_DIR} --with-thread --with-filesystem --with-system --with-date_time --with-program_options  --with-atomic  address-model=${Boost_address_model} link=static,shared ${boost_toolset}
#		INSTALL_COMMAND 		""
#)


externalproject_add(boost
		BUILD_IN_SOURCE 		1
		URL						https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz
		SOURCE_DIR              "${SRC_DIR}/boost"
		UPDATE_COMMAND 			""
		CONFIGURE_COMMAND 		"${Boost_Bootstrap_Command}"
		BUILD_COMMAND 			${Boost_b2_Command}
		#INSTALL_COMMAND 		${Boost_b2_Command} install
		INSTALL_COMMAND 		""
		)
externalproject_add_steptargets(boost build install)

# LibrdKafka
externalproject_add(librdkafka
		GIT_REPOSITORY			https://github.com/edenhill/librdkafka.git
		GIT_TAG                 master
		SOURCE_DIR              "${SRC_DIR}/librdkafka"
		BINARY_DIR              "${BUILD_DIR}/librdkafka"
		)
externalproject_add_steptargets(librdkafka build install)

#JSON
externalproject_add(json
	GIT_REPOSITORY		https://github.com/nlohmann/json.git
	GIT_TAG			master
	SOURCE_DIR		"${SRC_DIR}/json"
	BINARY_DIR		"${BUILD_DIR}/json"
)
externalproject_add_steptargets(json build install)

#Libtins
externalproject_add(libtins
        GIT_REPOSITORY          https://github.com/mfontanini/libtins.git
        GIT_TAG                 master
        SOURCE_DIR              "${SRC_DIR}/libtins"
        BINARY_DIR              "${BUILD_DIR}/libtins"
		CMAKE_ARGS				"-DLIBTINS_ENABLE_CXX11=1"
)
externalproject_add_steptargets(libtins build install)

#CPPKafka
externalproject_add(cppkafka
		GIT_REPOSITORY          https://github.com/mfontanini/cppkafka.git
		GIT_TAG                 master
		SOURCE_DIR              "${SRC_DIR}/cppkafka"
		BINARY_DIR              "${BUILD_DIR}/cppkafka"
		CMAKE_ARGS				"-DCPPKAFKA_RDKAFKA_STATIC_LIB=ON"
		)
externalproject_add_steptargets(cppkafka build install)

add_dependencies(passivedns boost librdkafka json libtins cppkafka)


target_link_libraries(passivedns "${TINS_LIBRARY}" "${RDKAFKA_LIBRARY}" "${BUILD_DIR}/cppkafka/lib/libcppkafka.so")
#target_link_libraries(passivedns "${TINS_LIBRARY}" "${RDKAFKA_LIBRARY}" "/usr/local/lib64/libcppkafka.so")
