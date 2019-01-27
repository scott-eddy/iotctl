cmake_minimum_required(VERSION 3.1)

project(iotctl LANGUAGES CXX)


set(CMAKE_VERBOSE_MAKEFILE, ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_SYSTEM_NAME STREQUAL "Android" AND NOT DEFINED ANDROID_SDK_ROOT)
    message(FATAL_ERROR "ANDROID_SDK_ROOT build target specified. Must be one of <TODO>")
    message(STATUS "Android NDK is: ${CMAKE_ANDROID_NDK}")
else()
    message(STATUS "Building for: ${CMAKE_SYSTEM_NAME}, ${CMAKE_ANDROID_ARCH_ABI}")
endif()

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)
