cmake_minimum_required(VERSION 3.10)
project(Curves3D LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Собираем динамическую библиотеку
add_library(curves SHARED src/curve3d.cpp)

# настраиваем include и экспорт
target_include_directories(curves PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_definitions(curves PRIVATE CURVES_LIBRARY)

# Собираем исполняемый файл
add_executable(main_app app/main.cpp)

target_include_directories(main_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Линкуем
target_link_libraries(main_app PRIVATE curves)

# Включение OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(main_app PRIVATE OpenMP::OpenMP_CXX)
else()
    message(WARNING "OpenMP not found — falling back to sequential sum")
endif()