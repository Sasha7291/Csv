cmake_minimum_required(VERSION 3.16)

project(Csv LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Csv
    main.cpp
    reader.hpp
    row.hpp
    iterator.hpp
    range.hpp
    exception.hpp
    writer.hpp
)

include(GNUInstallDirs)
install(TARGETS Csv
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
