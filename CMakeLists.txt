cmake_minimum_required(VERSION 3.0.2)

project(ilo_li_sina VERSION 0.0)

set(pokiPiPokiPiNimiWawa src)
file(GLOB_RECURSE pokiPiNimiWawa ${pokiPiPokiPiNimiWawa}/*.cpp)
set(pokiPiNimiWawaPiILO_LI_SINAAla include)

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} ${pokiPiNimiWawa})
target_include_directories(${PROJECT_NAME} PRIVATE ${pokiPiNimiWawaPiILO_LI_SINAAla})

find_package(PythonInterp REQUIRED)

# TODO lipu pi nimi toki li ante ala la o pali ala e ni
add_custom_target(
 pali ALL
 COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/paliELipuToki.py
 BYPRODUCTS ${pokiPiPokiPiNimiWawa}/ante_toki/nimi_poki.hpp
 COMMENT "li pali e poki pi nimi nimi en nimi tawa jan"
)
add_dependencies(${PROJECT_NAME} pali)