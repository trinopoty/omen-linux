cmake_minimum_required(VERSION 3.17)
project(OmenLinux)

set(CMAKE_CXX_STANDARD 14)

include("CMakePaths.txt" OPTIONAL)

set(Qt5Core_DIR "${Qt_DIR}/Qt5Core")
set(Qt5Gui_DIR "${Qt_DIR}/Qt5Gui")
set(Qt5Widgets_DIR "${Qt_DIR}/Qt5Widgets")

set(CMAKE_AUTOMOC ON)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(include)

set(QtIncludes src/OmenModule.cpp)
qt5_wrap_cpp(QtIncludes include/OmenModule.h)
add_library(OmenLinux-QtIncludes STATIC ${QtIncludes})
target_link_libraries(OmenLinux-QtIncludes Qt5::Core)
target_link_libraries(OmenLinux-QtIncludes Qt5::Gui)
target_link_libraries(OmenLinux-QtIncludes Qt5::Widgets)

add_library(FourZone STATIC
        src/modules/FourZoneKbLight/FourZoneKbLight.cpp
        src/modules/FourZoneKbLight/FourZoneKbLightInternal.cpp
        src/modules/FourZoneKbLight/FourZoneKbLightDriver.cpp
        src/modules/FourZoneKbLight/FourZoneKbLightWidget.cpp
        src/modules/FourZoneKbLight/ColorLineEditControl.cpp)
target_link_libraries(FourZone Qt5::Core)
target_link_libraries(FourZone Qt5::Gui)
target_link_libraries(FourZone Qt5::Widgets)
target_link_libraries(FourZone OmenLinux-QtIncludes)

add_executable(OmenLinux
        src/main.cpp
        src/MainWindow.cpp)
target_link_libraries(OmenLinux Qt5::Core)
target_link_libraries(OmenLinux Qt5::Gui)
target_link_libraries(OmenLinux Qt5::Widgets)
target_link_libraries(OmenLinux OmenLinux-QtIncludes)
target_link_libraries(OmenLinux FourZone)
