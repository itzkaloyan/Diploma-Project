cmake_minimum_required(VERSION 3.16)
project(Client LANGUAGES CXX)

add_subdirectory(cppClientLib build)

set(SOURCES
    main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cppClientLib/src/includes
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    serverClient
)