cmake_minimum_required(VERSION 3.18)
project( robotProject )

find_package( OpenCV REQUIRED )
find_package(nlohmann_json 3.2.0 )

add_subdirectory(cppClientLib) # build)

set(SOURCES
    main.cpp
    movement.cpp
    robot.cpp

)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cppClientLib/src/includes
    ${OpenCV_INCLUDE_DIRS}.
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    nlohmann_json::nlohmann_json
    serverClient
    ${OpenCV_LIBS}
)
