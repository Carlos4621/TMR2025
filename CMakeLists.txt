cmake_minimum_required(VERSION 3.5)

project(TMR VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia Concurrent)
find_package(OpenCV REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TMR
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        YOLOv8Model.h
        YOLOv8Model.cpp
        PredictionsData.h
        VideoRecoWidget.h VideoRecoWidget.cpp
        Susurrador.h Susurrador.cpp
        VoiceRecoWidget.h VoiceRecoWidget.cpp

        VoiceRecorder.h VoiceRecorder.cpp

    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TMR APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

else()
    if(ANDROID)
        add_library(TMR SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TMR
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TMR PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Concurrent whisper)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TMR)
endif()
set_target_properties(TMR PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TMR
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TMR)
endif()
