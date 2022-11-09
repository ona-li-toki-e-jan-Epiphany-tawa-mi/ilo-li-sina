cmake_minimum_required(VERSION 3.0.2)

project(ilo_li_sina VERSION 1.0.0)


file(GLOB_RECURSE pokiPiNimiWawa ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} ${pokiPiNimiWawa})
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


# li pali e ante toki.
find_package(PythonInterp REQUIRED)
set(lipuPiPaliPiLipuToki       ${CMAKE_CURRENT_SOURCE_DIR}/paliELipuToki.py)
file(GLOB pokiPiLipuPiNimiToki ${CMAKE_CURRENT_SOURCE_DIR}/nimi_en_toki/*.lang)
set(lipuPiAnteToki             ${CMAKE_CURRENT_SOURCE_DIR}/src/ante_toki/nimi_toki.hpp)

add_custom_command(
    COMMAND ${PYTHON_EXECUTABLE}    ${lipuPiPaliPiLipuToki}
    DEPENDS ${pokiPiLipuPiNimiToki} ${lipuPiPaliPiLipuToki}
    OUTPUT  ${lipuPiAnteToki}
    COMMENT "li pali e poki pi nimi nimi en nimi tawa jan"
)
add_custom_target(
    anteToki ALL
    DEPENDS  ${lipuPiAnteToki}
)
add_dependencies(${PROJECT_NAME} anteToki)