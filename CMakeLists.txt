cmake_minimum_required(VERSION 3.1)

project(iotctl LANGUAGES CXX)


set(CMAKE_VERBOSE_MAKEFILE, ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "ABI is: ${ANDROID_ABI}")
message(STATUS "STD C++ is: ${ANDROID_STL}")
message(STATUS "C++ Std include dirs are: ${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES}")
message(STATUS "C Std include dirs are: ${CMAKE_C_STANDARD_INCLUDE_DIRECTORIES}")
message(STATUS "Sysroot is: ${CMAKE_SYSROOT}")
message(STATUS "C++ compiler is: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "C++ Linker flags: ${CMAKE_EXE_LINKER_FLAGS}")

if(ANDROID_ABI STREQUAL "armeabi-v7a") 
    set(QT_Android_ABI_DIR "android_armv7")
    # Explicitly include the system headers as passing --sysroot does not actually
    # Allow clang to find them
    # http://lists.llvm.org/pipermail/cfe-users/2016-March/000923.html
endif()

message(STATUS "Android ABI: ${QT_Android_ABI_DIR}")
set(Qt5Core_DIR "${QT_INSTALL_ROOT}/${QT_Android_ABI_DIR}/lib/cmake/Qt5Core")
set(Qt5Gui_DIR "${QT_INSTALL_ROOT}/${QT_Android_ABI_DIR}/lib/cmake/Qt5Gui")
set(Qt5Network_DIR "${QT_INSTALL_ROOT}/${QT_Android_ABI_DIR}/lib/cmake/Qt5Network")
set(Qt5Qml_DIR "${QT_INSTALL_ROOT}/${QT_Android_ABI_DIR}/lib/cmake/Qt5Qml")
set(Qt5Quick_DIR "${QT_INSTALL_ROOT}/${QT_Android_ABI_DIR}/lib/cmake/Qt5Quick")
set(Qt5_DIR "${QT_INSTALL_ROOT}/${QT_Android_ABI_DIR}/lib/cmake/Qt5")

message(STATUS "Qt5_DIR: ${Qt5_DIR}")
list(APPEND CMAKE_PREFIX_PATH "${QT_INSTALL_ROOT}/${QT_Android_ABI_DIR}/lib/cmake/Qt5")

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)
