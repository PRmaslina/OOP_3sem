cmake_minimum_required(VERSION 3.19)
project(Server LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Network)

qt_standard_project_setup()

qt_add_executable(Server
    main.cpp
    server.h server.cpp
    polynom.h polynom.cpp
    complex.h complex.cpp
    number.h
    array.h array.cpp

)

target_link_libraries(Server
    PRIVATE
        Qt::Core
        Qt::Network
)

include(GNUInstallDirs)

install(TARGETS Server
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
