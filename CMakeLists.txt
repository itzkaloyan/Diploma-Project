cmake_minimum_required(VERSION 3.16)
project(Client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(cppClientLib build)
set(SOURCES
    main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cppClientLib/src/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/cppClientLib/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    serverClient
)