cmake_minimum_required(VERSION 3.19)
project(4_PractOOP LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(4_PractOOP
    WIN32 MACOSX_BUNDLE
    main.cpp
    interface.cpp
    interface.h
    interface.ui
    polynom.cpp
    complex.cpp
    array.cpp


    array.h
    complex.h
    number.h
    polynom.h
)

target_link_libraries(4_PractOOP
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS 4_PractOOP
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET 4_PractOOP
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
