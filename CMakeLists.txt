cmake_minimum_required(VERSION 3.19)
project(VirtualDeviceManager LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)
find_package(QtZeroConf REQUIRED)

qt_standard_project_setup()

qt_add_executable(VirtualDeviceManager
    WIN32 MACOSX_BUNDLE
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
)

target_link_libraries(VirtualDeviceManager
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        QtZeroConf
)

install(TARGETS VirtualDeviceManager
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET VirtualDeviceManager
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
