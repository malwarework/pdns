include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

cmake_minimum_required(VERSION 3.9.2)
project(passivedns)
set(CMAKE_CXX_STANDARD 14)
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
file(COPY lib/librdkafka DESTINATION ${CMAKE_BINARY_DIR}/lib)
file(COPY lib/libtins DESTINATION ${CMAKE_BINARY_DIR}/lib)
file(COPY lib/cppkafka DESTINATION ${CMAKE_BINARY_DIR}/lib)
file(COPY lib/boost DESTINATION ${CMAKE_BINARY_DIR}/lib)

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

set(SOURCE_FILES src/main.cpp src/TrafficeVolumeReduction.cpp include/TrafficeVolumeReduction.h include/config.h src/PeriodicListPrunning.cpp include/PeriodicListPrunning.h src/KafkaConnector.cpp include/KafkaConnector.h)
add_executable(passivedns ${SOURCE_FILES})

target_include_directories(passivedns PRIVATE ${boost_INCLUDE_DIR} ${librdkafka_INCLUDE_DIR} ${json_INCLUDE_DIR} ${libtins_INCLUDE_DIR} ${cppkafka_INCLUDE_DIR})
target_link_libraries(passivedns "${TINS_LIBRARY}" "${RDKAFKA_LIBRARY}" "${CPPKAFKA_LIBRARY}" ${OPTIONS_LIBRARY} nlohmann_json::nlohmann_json)

install(TARGETS passivedns RUNTIME DESTINATION bin PERMISSIONS OWNER_EXECUTE)
install(FILES passivedns.conf PERMISSIONS OWNER_WRITE TYPE SYSCONF)
install(DIRECTORY lib/librdkafka/lib/ DESTINATION lib)
install(DIRECTORY lib/librdkafka/include/ DESTINATION include)
install(DIRECTORY lib/libtins/lib/ DESTINATION lib)
install(DIRECTORY lib/libtins/include/ DESTINATION include)
install(DIRECTORY lib/cppkafka/lib/ DESTINATION lib)
install(DIRECTORY lib/cppkafka/include/ DESTINATION include)
install(FILES lib/boost/lib/libboost_program_options.a lib/boost/lib/libboost_program_options.so lib/boost/lib/libboost_program_options.so.1 lib/boost/lib/libboost_program_options.so.1.70.0 lib/boost/lib/libboost_program_options.so.1.70 DESTINATION lib)
install(DIRECTORY lib/boost/include/boost/program_options DESTINATION include/boost)
set(CPACK_TGZ_COMPONENT_INSTALL ON)
set(CPACK_COMPONENT_ALL deb)
set(CPACK_COMPONENTS_ALL deb)
set(CPACK_GENERATOR "DEB")
include(CPack)