cmake_minimum_required(VERSION 3.16)

set(CSV_LIB_NAME csv)

add_library(${CSV_LIB_NAME} INTERFACE)
target_include_directories(${CSV_LIB_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
