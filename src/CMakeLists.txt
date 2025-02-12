cmake_minimum_required(VERSION 3.5)

project(2024-JCO-The-Legend-of-Chiup-Chiup-ALE VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia SvgWidgets)

set(PROJECT_SOURCES
        main.cpp
        mainfrm.cpp
        mainfrm.h
        mainfrm.ui
)

# Il faut ajouter *MANUELLEMENT* cette ligne afin de pouvoir faire une promotion de Widget dans un UI.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(2024-JCO-The-Legend-of-Chiup-Chiup-ALE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        gamecanvas.h
        gamecore.h
        gamescene.h
        gameview.h
		resources.h
		sprite.h
		spritetickhandler.h
		utilities.h
        gamecanvas.cpp
        gamecore.cpp
        gamescene.cpp
        gameview.cpp
		resources.cpp
		sprite.cpp
		spritetickhandler.cpp
		utilities.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 2024-JCO-The-Legend-of-Chiup-Chiup-ALE APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(2024-JCO-The-Legend-of-Chiup-Chiup-ALE SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(2024-JCO-The-Legend-of-Chiup-Chiup-ALE
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(2024-JCO-The-Legend-of-Chiup-Chiup-ALE PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(2024-JCO-The-Legend-of-Chiup-Chiup-ALE PRIVATE Qt6::Multimedia)
target_link_libraries(2024-JCO-The-Legend-of-Chiup-Chiup-ALE PRIVATE Qt6::SvgWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.2024-JCO-The-Legend-of-Chiup-Chiup-ALE)
endif()
set_target_properties(2024-JCO-The-Legend-of-Chiup-Chiup-ALE PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS 2024-JCO-The-Legend-of-Chiup-Chiup-ALE
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(2024-JCO-The-Legend-of-Chiup-Chiup-ALE)
endif()

