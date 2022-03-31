cmake_minimum_required (VERSION 2.6)

set(PROJECT_NAME ilo_li_sina)
set(SOURCE_DIR src)
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

project (${PROJECT_NAME})

add_compile_options("-std=c++17")
add_executable(ilo_li_sina ${SOURCES})
