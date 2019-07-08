cmake_minimum_required (VERSION 2.6)
project (Moostard)

set (MOOSTARD_VERSION_MAJOR 1)
set (MOOSTARD_VERSION_MINOR 2)

configure_file(
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/src/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")

add_library(brainfuck_interpretor src/bfinterpretor.cpp)

add_executable(moostar src/main.cpp)

target_link_libraries(moostar brainfuck_interpretor)

install (TARGETS moostar DESTINATION bin)
