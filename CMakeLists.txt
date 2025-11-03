cmake_minimum_required(VERSION 3.19)

set(PROJECT_NAME PotionEmporium)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(PROJECT_SOURCES
    src/main.cpp
    src/ErrorHandling.cpp
)

set(PROJECT_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/Potion.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Player.h
    ${CMAKE_CURRENT_LIST_DIR}/include/ErrorHandling.h
)

add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_compile_options(${PROJECT_NAME} PRIVATE 
    -Werror 
    -pedantic-errors 
    -Wall
    -Weffc++ 
    -Wextra
    -Wconversion
    -Wsign-conversion
    -Wshadow
    )


include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
