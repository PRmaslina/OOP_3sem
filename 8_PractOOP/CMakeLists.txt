cmake_minimum_required(VERSION 3.19)
project(8_PractOOP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Найдите все необходимые компоненты Qt
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Charts)

qt_standard_project_setup()

# Добавьте определение для использования Qt Charts
add_definitions(-DQT_CHARTS_LIB)

# Перечислите все исходные файлы
set(SOURCES
    main.cpp
    mainwindow.cpp
    complex.cpp
    polynom.cpp
)

set(HEADERS
    mainwindow.h
    complex.h
    cos.h
    function.h
    number.h
    polynom.h
    si.h
    sin.h
    array.h
)

set(FORMS
    mainwindow.ui
)

# Создайте исполняемый файл
qt_add_executable(8_PractOOP
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

# Настройте свойства цели
target_compile_features(8_PractOOP PRIVATE cxx_std_17)

# Подключите необходимые библиотеки Qt
target_link_libraries(8_PractOOP
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
)

# Если вы используете Q_OBJECT в заголовочных файлах, добавьте
qt6_wrap_cpp(MOC_SOURCES
    mainwindow.h
    complex.h
)

# Добавьте MOC файлы в исходники
target_sources(8_PractOOP PRIVATE ${MOC_SOURCES})

# Установите зависимости для сборки
add_custom_command(TARGET 8_PractOOP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Build completed successfully"
)

# Опции установки
include(GNUInstallDirs)

install(TARGETS 8_PractOOP
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Скрипт для деплоя
qt_generate_deploy_app_script(
    TARGET 8_PractOOP
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
