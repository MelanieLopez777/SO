cmake_minimum_required(VERSION 3.16)
project(Programa7 VERSION 1.0)

# Usar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar Qt6 y los componentes necesarios
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Activar el Meta-Object Compiler (MOC)
set(CMAKE_AUTOMOC ON)

# Incluir las subcarpetas para los #includes
include_directories(
    .
    Calc
    Clock
    Generador
    Queue
    Structure
)

# Añadir el ejecutable y todos sus archivos fuente
add_executable(SimuladorProcesos
    main.cpp
    Interface/mainwindow.h
    Interface/mainwindow.cpp
    TablaBCP/bcpwindow.h
    TablaBCP/bcpwindow.cpp
    TablaMemoria/memorywindow.h
    TablaMemoria/memorywindow.cpp
    Scheduler/scheduler.h
    Scheduler/scheduler.cpp
    Calc/operations.h
    Calc/operations.cpp
    Clock/clock.h
    Clock/clock.cpp
    Generador/generadorDatos.h
    Generador/generadorDatos.cpp
    Queue/queue.h
    Structure/structures.h
    Structure/structures.cpp
)

# Vincular las bibliotecas de Qt al ejecutable
target_link_libraries(SimuladorProcesos PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)