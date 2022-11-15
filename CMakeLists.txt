cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_CXX_STANDARD 17)
project(ilo_li_sina VERSION 1.0.0)



if (UNIX)
    set(lawaOS UNIX)
    find_library(TERMINFO NAMES terminfo tinfo curses ncurses ncursesw)
elseif (WIN32)
    set(lawaOS WINDOWS)
endif ()



file(GLOB_RECURSE pokiPiNimiWawa ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${pokiPiNimiWawa})
add_compile_definitions(${lawaOS} NANPA_PI_ILO_PI_ILO_LI_SINA=\"${CMAKE_PROJECT_VERSION}\")
target_link_libraries(${CMAKE_PROJECT_NAME} ${TERMINFO})
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)



# li pali e ante toki.
find_package(PythonInterp REQUIRED)
if (NOT ${PYTHON_VERSION_MAJOR} STREQUAL 3)
    message(FATAL_ERROR "ilo pi toki Python pi nanpa 3 anu suli tawa 3 li wile! li kama jo e " 
                        ${PYTHON_VERSION_MAJOR} "! (nanpa ali li '" ${PYTHON_VERSION_STRING} "')")
endif()

set(lipuPiPaliPiLipuToki       ${CMAKE_CURRENT_SOURCE_DIR}/paliELipuToki.py)
file(GLOB pokiPiLipuPiNimiToki ${CMAKE_CURRENT_SOURCE_DIR}/nimi_en_toki/*.lang)
set(lipuPiAnteToki             ${CMAKE_CURRENT_SOURCE_DIR}/src/ante_toki/nimi_toki.hpp)

add_custom_command(
    COMMAND ${PYTHON_EXECUTABLE} ${lipuPiPaliPiLipuToki}
    DEPENDS ${pokiPiLipuPiNimiToki} ${lipuPiPaliPiLipuToki}
    OUTPUT  ${lipuPiAnteToki}
    COMMENT "li pali e poki pi nimi nimi en nimi tawa jan"
)
add_custom_target(
    anteToki ALL
    DEPENDS  ${lipuPiAnteToki}
)
add_dependencies(${CMAKE_PROJECT_NAME} anteToki)