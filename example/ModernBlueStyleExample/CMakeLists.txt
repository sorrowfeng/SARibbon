cmake_minimum_required(VERSION 3.15)
SET(VERSION_SHORT 0.1)
project(ModernBlueStyleExample VERSION ${VERSION_SHORT})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} 5.12 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(ModernBlueStyleExample
    ModernBlueStyleWindow.h
    ModernBlueStyleWindow.cpp
    main.cpp
)

if(WIN32)
    set_target_properties(ModernBlueStyleExample PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(NOT TARGET SARibbonBar)
    # 说明这个例子是单独加载
    message(STATUS "NOT TARGET SARibbonBar find_package(SARibbonBar REQUIRED)")
    find_package(SARibbonBar REQUIRED)
endif()

target_link_libraries(ModernBlueStyleExample PRIVATE SARibbonBar::SARibbonBar)
target_link_libraries(ModernBlueStyleExample PRIVATE
                                       Qt${QT_VERSION_MAJOR}::Core
                                       Qt${QT_VERSION_MAJOR}::Gui
                                       Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ModernBlueStyleExample PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
    CXX_EXTENSIONS OFF
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    VERSION ${SARIBBON_VERSION}
    EXPORT_NAME ModernBlueStyleExample
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
include(GNUInstallDirs)
install(TARGETS ModernBlueStyleExample
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ModernBlueStyleExample)
endif()
