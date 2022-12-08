cmake_minimum_required(VERSION 3.5)

project(test_recognition_visual VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt5Charts REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/FaceRecognitionTest)

set(PROJECT_SOURCES
    FaceRecognitionTest/_Image.cpp
    FaceRecognitionTest/histogram_method.cpp
    FaceRecognitionTest/lbph_method.cpp
    FaceRecognitionTest/random_pixels_method.cpp
    FaceRecognitionTest/recognition_call.cpp
    FaceRecognitionTest/scaling_method.cpp
    FaceRecognitionTest/test_method.cpp
    FaceRecognitionTest/voting_method.cpp
    histogrammethod.cpp
    lbphmethod.cpp
    main.cpp
    mainwindow.cpp
    randommethod.cpp
    scalingmethod.cpp
    votingmethod.cpp
)

set(HEADER_FILES
    FaceRecognitionTest/_Image.h
    FaceRecognitionTest/all_libraries.h
    FaceRecognitionTest/histogram_method.h
    FaceRecognitionTest/lbph_method.h
    FaceRecognitionTest/random_pixels_method.h
    FaceRecognitionTest/recognition_call.h
    FaceRecognitionTest/scaling_method.h
    FaceRecognitionTest/test_method.h
    FaceRecognitionTest/voting_method.h
    histogrammethod.h
    lbphmethod.h
    mainwindow.h
    randommethod.h
    scalingmethod.h
    votingmethod.h
)

set(UIS
    histogrammethod.ui
    lbphmethod.ui
    mainwindow.ui
    randommethod.ui
    scalingmethod.ui
    votingmethod.ui
)

QT5_WRAP_UI( UI_HEADERS ${UIS} )

file(COPY ${PROJECT_SOURCE_DIR}/AT&T_grayscale_normilized DESTINATION ${PROJECT_BINARY_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(windowapp_anonymization
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${HEADER_FILES}
        ${UI_HEADERS}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET windowapp_anonymization APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(test_recognition_visual SHARED
            ${PROJECT_SOURCES}
            ${HEADER_FILES}
            ${UI_HEADERS}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(test_recognition_visual
            ${PROJECT_SOURCES}
            ${HEADER_FILES}
            ${UI_HEADERS}
        )
    endif()
endif()

target_link_libraries(test_recognition_visual PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts -static)


set_target_properties(test_recognition_visual PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS test_recognition_visual
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(test_recognition_visual)
endif()
