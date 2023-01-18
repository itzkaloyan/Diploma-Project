cmake_minimum_required(VERSION 3.18)
project( robotProject )

find_package( OpenCV REQUIRED )

add_subdirectory(cppClientLib build)

set(SOURCES
    src/main.cpp 
    src/robot.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cppClientLib/src/includes
    ${OpenCV_INCLUDE_DIRS}
    src/
    )

target_link_libraries(${PROJECT_NAME} PUBLIC
    serverClient
    ${OpenCV_LIBS}
    )
