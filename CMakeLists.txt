cmake_minimum_required(VERSION 3.12)

project(OpenGLTutorial CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

add_subdirectory(shaders)

# Copy data folder
execute_process(COMMAND ${CMAKE_COMMAND} -E 
	copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data)