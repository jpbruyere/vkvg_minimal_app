cmake_minimum_required(VERSION 3.14)

project(vkvg_minimal_app)

find_library(VKVG_LIBRARY NAMES vkvg)

FILE(GLOB sources src/*.c)

add_executable(${PROJECT_NAME} ${sources})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
	${VKVG_LIBRARY}
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	ADD_DEFINITIONS (-DDEBUG)
ENDIF()

