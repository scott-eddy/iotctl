cmake_minimum_required(VERSION 3.1)
project(iotctl LANGUAGES CXX)
set(CMAKE_VERBOSE_MAKEFILE, ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Compiling for ${CMAKE_SYSTEM_NAME}")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
  message(STATUS "ABI is: ${ANDROID_ABI}")
  message(STATUS "STD C++ is: ${ANDROID_STL}")
  include(cmake/qt-android-mk-apk.cmake)
  # TODO: Require this is passed in
  message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
endif()

find_package(Qt5 COMPONENTS Core Quick Gui Network REQUIRED)
get_filename_component(QT5_INSTALL_PREFIX "${Qt5Core_DIR}/../../.." ABSOLUTE)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    add_library(${PROJECT_NAME} SHARED "main.cpp" "qml.qrc")
    qt_android_build_apk(
      TARGET ${PROJECT_NAME}
      PACKAGE_NAME org.example.QmlCmakeDemo
      QML_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}
      ANDROID_EXTRA_FILES ${QT5_INSTALL_PREFIX}/src/android/templates/
    )
else()
    add_executable(${PROJECT_NAME}
      main.cpp
      qml.qrc)
endif()
target_include_directories(${PROJECT_NAME}
    PUBLIC
    include)
target_sources(${PROJECT_NAME}
  PRIVATE
  src/iotctl_light.cpp
  src/iotctl_light_control.cpp
  )
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Qml Qt5::Gui)
