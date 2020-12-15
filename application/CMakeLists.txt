cmake_minimum_required(VERSION 3.17)
project(OmenLinux)

set(CMAKE_CXX_STANDARD 17)

include("CMakePaths.txt" OPTIONAL)

set(Qt5Core_DIR "${Qt_DIR}/Qt5Core")
set(Qt5Gui_DIR "${Qt_DIR}/Qt5Gui")
set(Qt5Widgets_DIR "${Qt_DIR}/Qt5Widgets")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

add_executable(OmenLinux src/main.cpp src/MainWindow.cpp src/MainWindow.h)

target_link_libraries(OmenLinux Qt5::Core)
target_link_libraries(OmenLinux Qt5::Gui)
target_link_libraries(OmenLinux Qt5::Widgets)
