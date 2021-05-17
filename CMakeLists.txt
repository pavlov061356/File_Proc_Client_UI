cmake_minimum_required(VERSION 3.5)

project(File_Proc_Client_UI LANGUAGES CXX)
set(CMAKE_PREFIX_PATH "/home/vladimir/Qt/5.15.2/gcc_64")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_VERSION 5)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()
set(REQUIRED_LIBS Core WebSockets Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::WebSockets Qt5::Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        websocketclient.h
        websocketclient.cpp
)

add_executable(File_Proc_Client_UI
        ${PROJECT_SOURCES})


find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(File_Proc_Client_UI ${REQUIRED_LIBS_QUALIFIED})
