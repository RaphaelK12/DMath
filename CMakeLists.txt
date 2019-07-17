cmake_minimum_required(VERSION 3.12)
project(DMath)

set(CMAKE_CXX_STANDARD 17)

set(LIB_NAME ${PROJECT_NAME})

##
## TARGET
## create target and add include path
##
add_library(${LIB_NAME} INTERFACE)
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

target_include_directories(
    ${LIB_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Compile example
#set(COMPILE_EXAMPLES 1)
if (${COMPILE_EXAMPLES})
	set(EXAMPLE1_NAME "Example")

	add_executable(${EXAMPLE1_NAME} "examples/example1.cpp" "examples/yo.cpp")

	#target_compile_options(${EXAMPLE1_NAME} PUBLIC /arch:AVX)

	target_link_libraries(${EXAMPLE1_NAME} ${LIB_NAME}::${LIB_NAME})
endif()