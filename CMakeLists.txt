cmake_minimum_required(VERSION 3.5)

project(project_for_smi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add Qt5 or Qt6 components including MultimediaWidgets
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Multimedia MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Multimedia MultimediaWidgets)

# Set project sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui



    adding_into_article.h adding_into_article.cpp adding_into_article.ui
    adding_into_author.h adding_into_author.cpp adding_into_author.ui
    adding_into_edition.h adding_into_edition.cpp adding_into_edition.ui
    adding_into_journal.h adding_into_journal.cpp adding_into_journal.ui
    adding_records.h adding_records.cpp adding_records.ui
    author_search.h author_search.cpp author_search.ui
    hot_news.h hot_news.cpp hot_news.ui
    registration.h registration.cpp registration.ui
    update_data.h update_data.cpp update_data.ui
    resource_qt.qrc
)

# Add executable or library depending on platform and Qt version
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(project_for_smi
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        databasemanger.h databasemanger.cpp databasemanger.ui
        tariffuserwindow.h tariffuserwindow.cpp tariffuserwindow.ui
        adding_into_work.h adding_into_work.cpp adding_into_work.ui
        select_from_article.h select_from_article.cpp select_from_article.ui
    )
else()
    if(ANDROID)
        add_library(project_for_smi SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(project_for_smi
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link libraries
target_link_libraries(project_for_smi PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)

# Set properties for macOS or Windows
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.project_for_smi)
endif()
set_target_properties(project_for_smi PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install targets
include(GNUInstallDirs)
install(TARGETS project_for_smi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(WIN32)
    # Устанавливаем масштаб DPI на 1
    set(ENV{QT_SCALE_FACTOR} 1)
endif()


# Finalize executable for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(project_for_smi)
endif()
