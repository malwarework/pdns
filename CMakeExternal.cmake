include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

cmake_minimum_required(VERSION 3.9.2)
set(CMAKE_CXX_STANDARD 14)
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



include(ExternalProject)
#boost
externalproject_add(boost
        BUILD_IN_SOURCE			1
        PREFIX					boost
        URL						https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz
        TLS_VERIFY				0
        CONFIGURE_COMMAND		./bootstrap.sh --prefix=<INSTALL_DIR>
        UPDATE_COMMAND			""
        BUILD_COMMAND			./b2 install
        INSTALL_COMMAND			""
        INSTALL_DIR				${boost_INSTALL}
        )
externalproject_add_steptargets(boost build install)

# LibrdKafka
externalproject_add(librdkafka
        BUILD_IN_SOURCE      	1
        DEPENDS					boost
        PREFIX					librdkafka
        GIT_REPOSITORY			https://github.com/edenhill/librdkafka.git
        CONFIGURE_COMMAND		./configure --prefix=<INSTALL_DIR>
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
        CMAKE_ARGS              -DLIBTINS_ENABLE_CXX11=1 -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
        INSTALL_DIR             ${libtins_INSTALL}
        )
externalproject_add_steptargets(libtins build install)

#CPPKafka
externalproject_add(cppkafka
        BUILD_IN_SOURCE         1
        DEPENDS                 librdkafka
        PREFIX                  cppkafka
        GIT_REPOSITORY          https://github.com/mfontanini/cppkafka.git
        CMAKE_ARGS              -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DBOOST_ROOT=${boost_INSTALL}
        INSTALL_DIR             ${cppkafka_INSTALL}
        )
externalproject_add_steptargets(cppkafka build install)