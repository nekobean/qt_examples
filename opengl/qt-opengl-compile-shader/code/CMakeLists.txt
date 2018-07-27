cmake_minimum_required(VERSION 3.1.0)

project(sample)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(OpenGL)

file(GLOB_RECURSE CPP_FILES src/*.cpp)
file(GLOB_RECURSE UI_FILES src/*.ui)
file(GLOB_RECURSE QRC_FILES res/*.qrc)

include_directories(src)

add_executable(${PROJECT_NAME}
    ${CPP_FILES}
    ${UI_FILES}
    ${QRC_FILES}
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    ${OPENGL_LIBRARY}
)
