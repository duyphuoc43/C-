cmake_minimum_required(VERSION 3.16)

project(AppTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

set(Boost_INCLUDE_DIR "/Users/admin/vcpkg/installed/arm64-osx/include")
# find_package(LibArchive REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(boost_system REQUIRED CONFIG)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appAppTest
    WebSocketClient.h
    WebSocketServer.h
    WebSocketClient.cpp
    WebSocketServer.cpp
    main.cpp
)

qt_add_qml_module(appAppTest
    URI AppTest
    VERSION 1.0
    QML_FILES
        Main.qml
)

set_target_properties(appAppTest PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAppTest
    PRIVATE Qt6::Quick Boost::boost Boost::filesystem Boost::system
)


include(GNUInstallDirs)
install(TARGETS appAppTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
