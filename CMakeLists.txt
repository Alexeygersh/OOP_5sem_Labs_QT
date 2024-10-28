cmake_minimum_required(VERSION 3.16)

project(OOP_Lab3_Gersh VERSION 0.1 LANGUAGES CXX)

# Настройки CMake для автоматической работы с Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка флагов компиляции для статической линковки
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

# Поиск Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Источники проекта
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Player.h
    Player.cpp
    PlayerContainer.h
    PlayerContainer.cpp
)

# Определение исполняемого файла для разных версий Qt
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OOP_Lab3_Gersh
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(OOP_Lab3_Gersh SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(OOP_Lab3_Gersh
            ${PROJECT_SOURCES}
            OnlinePlayer.h
            utils.h
            OnlinePlayer.cpp
            Player_table.h
            Player_table.cpp
            PlayerDialog.h
            PlayerDialog.cpp
            PlayerDialog.ui
            OnlinePlayerDialog.h
            OnlinePlayerDialog.cpp
            OnlinePlayerDialog.ui


        )
    endif()
endif()

# Линковка с Qt
target_link_libraries(OOP_Lab3_Gersh PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Инсталляция
include(GNUInstallDirs)
install(TARGETS OOP_Lab3_Gersh
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Финализация Qt приложения для Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OOP_Lab3_Gersh)
endif()

# Подключение библиотеки Boost
set(BOOST_ROOT "C:/boost_1_86_0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Поиск необходимых компонентов Boost
# find_package(Boost 1.86.0 REQUIRED COMPONENTS serialization)



find_package(Boost 1.86 REQUIRED COMPONENTS serialization)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories("C:/boost_1_86_0/stage/lib")
    target_link_libraries(OOP_Lab3_Gersh PRIVATE ${Boost_LIBRARIES})
endif()
