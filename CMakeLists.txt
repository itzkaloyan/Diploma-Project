cmake_minimum_required(VERSION 3.16)
project(Client LANGUAGES CXX)

add_subdirectory(c++ build)

set(SOURCES
    main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    serverClient
)