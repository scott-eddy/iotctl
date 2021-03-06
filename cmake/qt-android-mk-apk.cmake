include(CMakeParseArguments)

set(QT_ANDROID_MK_APK_DIR ${CMAKE_CURRENT_LIST_DIR})

function(qt_android_build_apk)
    ####
    # Adapted from https://martin.rpdev.net/2018/08/04/building-android-projects-with-qt-creator-and-cmake.html
    ###
    set(options)
    set(oneValueArgs
        TARGET PACKAGE_NAME ANDROID_EXTRA_FILES QML_ROOT_PATH
        SDK_BUILD_TOOLS_VERSION EXTRA_LIBS)
    set(multiValueArgs)
    cmake_parse_arguments(
        APK "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Gather required variables to create the configuration file.

    find_package(Qt5 COMPONENTS Core REQUIRED)
    # Qt5Core_DIR now points to $Qt5InstallPrefix/lib/cmake/Qt5Core, so
    # we get the parent directory three times:
    get_filename_component(QT5_INSTALL_PREFIX "${Qt5Core_DIR}/../../.." ABSOLUTE)
    message(STATUS "Qt5 installed in ${QT5_INSTALL_PREFIX}")

    # Adjust QML root path if not set:
    if(NOT APK_QML_ROOT_PATH)
        set(APK_QML_ROOT_PATH $<TARGET_FILE_DIR:${APK_TARGET}>)
    endif()

    # Get the toolchain prefix which is where androiddeployqt will look for bin-utilities
    file(RELATIVE_PATH APK_NDK_TOOLCHAIN_PREFIX ${CMAKE_ANDROID_NDK} ${CMAKE_CXX_COMPILER})
    # Create a list from the relative path
    string(REPLACE "/" ";" APK_NDK_TOOLCHAIN_PREFIX ${APK_NDK_TOOLCHAIN_PREFIX})
    list(GET APK_NDK_TOOLCHAIN_PREFIX 1 APK_NDK_TOOLCHAIN_PREFIX)

    # Get path to the target:
    set(APK_TARGET_OUTPUT_FILENAME $<TARGET_FILE:${APK_TARGET}>)

    # Get Android SDK build tools version:
    message("SDK ENVIRONMENT VARIABLE $ENV{ANDROID_SDK}")
    set(ANDROID_SDK_ROOT $ENV{ANDROID_SDK})
    if(NOT APK_SDK_BUILD_TOOLS_VERSION)
        file(GLOB sdk_versions RELATIVE ${ANDROID_SDK_ROOT}/build-tools
            ${ANDROID_SDK_ROOT}/build-tools/*)
        list(GET sdk_versions -1 APK_SDK_BUILD_TOOLS_VERSION)
    endif()

    # Get the full path to the android STL
    # ANDROID_STL_FULL_PATH
    # Extract STL static vs .so (naming convention is <type>_<shared || static>
    string(REPLACE "_" ";" STL_POSTFIX_LIST ${ANDROID_STL})
    list(GET STL_POSTFIX_LIST 1 STL_POSTFIX)
    if(STL_POSTFIX STREQUAL "shared")
        set(STL_POSTFIX ".so")
    elseif(STL_POSTFIX STREQUAL "static")
        set(STL_POSTFIX ".a")
    else()
        message(FATAL_ERROR "Unrecognized STL library post-fix from ${ANDROID_STL}. Expected 'static ' or  'shared' but parsed ${STL_POSTFIX}")
    endif()
    # Joint location of all STL sources relative to NDK
    set(ANDROID_CXX_SOURCE_LOCATION "sources/cxx-stl/llvm-libc++/libs")
    set(ANDROID_STL_FULL_PATH "${CMAKE_ANDROID_NDK}/${ANDROID_CXX_SOURCE_LOCATION}/${ANDROID_ABI}/lib${ANDROID_STL}${STL_POSTFIX}")
    message(STATUS "APK generation with ANDROID_STL_FULL_PATH=${ANDROID_STL_FULL_PATH}")

    # Step 1: Create an intermediate config file. At this point,
    # the generator expressions will we use are not yet resolved.
    configure_file(
        ${QT_ANDROID_MK_APK_DIR}/qt-android-deployment.json.in
        ${CMAKE_CURRENT_BINARY_DIR}/${APK_TARGET}-config.json.pre)

    # Step 2: Run file(CONFIGURE ...) to create the final config JSON
    # with generator expressions resolved:
    file(
        GENERATE
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${APK_TARGET}-config.json
        INPUT ${CMAKE_CURRENT_BINARY_DIR}/${APK_TARGET}-config.json.pre)

    # Step 3: Create a custom target which will build our APK:
    set(APK_DIR ${CMAKE_CURRENT_BINARY_DIR}/${APK_TARGET}-apk-build)
    if(NOT APK_ANDROID_EXTRA_FILES)
      message(FATAL_ERROR "APK_ANDROID_EXTRA_FILES not set. Suggest using those in ${QT5_INSTALL_PREFIX}/src/android/templates/")
    else()
      message(STATUS "APK generation with APK_ANDROID_EXTRA_FILES=${APK_ANDROID_EXTRA_FILES}")
    endif()

    if(JAVA_HOME)
        set(ANDROIDDEPLOYQT_EXTRA_ARGS
            ${ANDROIDDEPLOYQT_EXTRA_ARGS} --jdk '${JAVA_HOME}')
    endif()
    if(CMAKE_BUILD_TYPE EQUAL "RELEASE")
        set(ANDROIDDEPLOYQT_EXTRA_ARGS
            ${ANDROIDDEPLOYQT_EXTRA_ARGS} --release)
        set(APK_FILENAME ${APK_TARGET}-apk-build-release-unsigned.apk)
    else()
        set(APK_FILENAME ${APK_TARGET}-apk-build-debug.apk)
    endif()

    message(STATUS "APK_TARGET: ${APK_TARGET}")
    message(STATUS "APK_DIR: ${APK_DIR}")
    message(STATUS "APK_ANDROID_EXTRA_FILES: ${APK_ANDROID_EXTRA_FILES}")
    add_custom_target(
        ${APK_TARGET}-apk
        #COMMAND ${CMAKE_COMMAND} -E remove_directory ${APK_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${QT5_INSTALL_PREFIX}/src/android/templates/
            ${APK_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${APK_ANDROID_EXTRA_FILES}/
            ${APK_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory
            ${APK_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}
        COMMAND ${CMAKE_COMMAND} -E copy
            ${APK_TARGET_OUTPUT_FILENAME}
            ${APK_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}
        COMMAND ${QT5_INSTALL_PREFIX}/bin/androiddeployqt
            --verbose
            --output ${APK_DIR}
            --input ${CMAKE_CURRENT_BINARY_DIR}/${APK_TARGET}-config.json
            --deployment bundled
            --gradle
            ${ANDROIDDEPLOYQT_EXTRA_ARGS}
    )

    # Step 4: Create a custom target which pushes the created APK onto
    # the device.
    message(STATUS "APK_FILENAME: ${APK_FILENAME}")
    # TODO differentiate betwen release and debug apk install builds?
    add_custom_target(
        ${APK_TARGET}-apk-install
        COMMAND ${ANDROID_SDK_ROOT}/platform-tools/adb install -r
            ${APK_DIR}/build/outputs/apk/debug/${APK_FILENAME}
        DEPENDS
            ${APK_TARGET}-apk
    )

endfunction()
