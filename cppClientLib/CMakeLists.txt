cmake_minimum_required(VERSION 3.16)
project(serverClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig)
find_package(cppzmq)

set(SOURCES
    src/example_main.cpp
)
set(LIB_SOURCES
	#code
    src/Client.cpp
    src/Server.cpp
    #zmq dependencies
    cppzmq/zmq.hpp
    libzmq/include/zmq.h
    libzmq/include/zmq_utils.h
    #dependencies
    src/dpd/json.hpp
    src/dpd/stbi_load.h
    src/dpd/depend.h
    src/dpd/stbi_write.h
    #json creating
    src/Json.cpp
)

set(STAND_ALONE FALSE)
if(STAND_ALONE)
    add_executable(serverClient ${LIB_SOURCES} ${SOURCES})
else()
    add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    cppzmq-static
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dpd
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    cppzmq-static
    ${CMAKE_DL_LIBS}
)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:MSVC>:>)