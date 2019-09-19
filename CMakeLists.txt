include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

cmake_minimum_required(VERSION 3.9.2)
project(passivedns)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lz -lssl -lcrypto -ldl")

set(Boost_DEBUG 1)

set( boost_INSTALL ${PROJECT_SOURCE_DIR}/lib/boost )
set( boost_INCLUDE_DIR ${boost_INSTALL}/include )
set( boost_LIB_DIR ${boost_INSTALL}/lib )

set( json_INSTALL ${PROJECT_SOURCE_DIR}/src/json )
set( json_INCLUDE_DIR ${json_INSTALL}/include )
set( json_LIB_DIR ${json_INSTALL}/lib )

set( libtins_INSTALL ${PROJECT_SOURCE_DIR}/lib/libtins )
set( libtins_INCLUDE_DIR ${libtins_INSTALL}/include )
set( libtins_LIB_DIR ${libtins_INSTALL}/lib )

set(JSON_BuildTests OFF CACHE INTERNAL "")

include_directories(src include)
add_subdirectory(lib/nlohmann_json)
file(COPY lib/libtins DESTINATION ${CMAKE_BINARY_DIR}/lib)
file(COPY lib/boost DESTINATION ${CMAKE_BINARY_DIR}/lib)

find_library(OPTIONS_LIBRARY
        boost_program_options
        PATHS ${boost_LIB_DIR}
        NO_DEFAULT_PATH)
if (NOT OPTIONS_LIBRARY)
        message("Cant find OPTIONS_LIBRARY")
endif ()

find_library(TINS_LIBRARY
        tins
        ${libtins_LIB_DIR}
        NO_DEFAULT_PATH)
if (NOT TINS_LIBRARY)
        message("Cant find TINS_LIBRARY")
endif ()

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

set(SOURCE_FILES src/main.cpp src/TrafficeVolumeReduction.cpp include/TrafficeVolumeReduction.h include/config.h src/PeriodicListPrunning.cpp include/PeriodicListPrunning.h include/httplib.h)
add_executable(passivedns ${SOURCE_FILES})

target_include_directories(passivedns PRIVATE ${boost_INCLUDE_DIR} ${json_INCLUDE_DIR} ${libtins_INCLUDE_DIR})
target_link_libraries(passivedns "${TINS_LIBRARY}" ${OPTIONS_LIBRARY} ${ZLIB_LIBRARIES} OpenSSL::Crypto OpenSSL::SSL nlohmann_json::nlohmann_json ${CMAKE_DL_LIBS})


install(TARGETS passivedns RUNTIME DESTINATION bin PERMISSIONS WORLD_EXECUTE)

install(DIRECTORY lib/libtins/lib/ DESTINATION lib)
install(DIRECTORY lib/libtins/include/ DESTINATION include)
install(DIRECTORY lib/boost/include/boost/program_options DESTINATION include/boost)

install(FILES passivedns.conf PERMISSIONS WORLD_WRITE WORLD_READ OWNER_WRITE OWNER_READ DESTINATION /etc/passivedns)
install(FILES lib/boost/lib/libboost_program_options.a lib/boost/lib/libboost_program_options.so lib/boost/lib/libboost_program_options.so.1 lib/boost/lib/libboost_program_options.so.1.70.0 lib/boost/lib/libboost_program_options.so.1.70 DESTINATION lib)
install(FILES passivedns.service PERMISSIONS WORLD_READ DESTINATION /etc/systemd/system)

set(CPACK_TGZ_COMPONENT_INSTALL ON)
set(CPACK_COMPONENT_ALL deb)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "systemd, libpcap-dev, zlib1g-dev, python-dev, libssl-dev, openssl")
set(CPACK_COMPONENTS_ALL deb)
set(CPACK_GENERATOR "RPM;DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PDNS")
set(CPACK_RPM_PACKAGE_LICENSE "GPL")
set(CPACK_RPM_PACKAGE_VENDOR "PDNS")
set(CPACK_PACKAGE_VERSION "2.5")
set(CPACK_PACKAGE_NAME "passivedns")
set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION})
include(CPack)