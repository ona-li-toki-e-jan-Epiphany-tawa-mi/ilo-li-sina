cmake_minimum_required(VERSION 3.0.0)

project(ilo_li_sina VERSION 0.0)

set(pokiPiPokiPiNimiWawa src)
file(GLOB_RECURSE pokiPiNimiWawa ${pokiPiPokiPiNimiWawa}/*.cpp)
set(pokiPiNimiWawaPiILO_LI_SINAAla include)

add_compile_options(-std=c++17)
add_executable(${PROJECT_NAME} ${pokiPiNimiWawa})
target_include_directories(${PROJECT_NAME} PRIVATE ${pokiPiNimiWawaPiILO_LI_SINAAla})