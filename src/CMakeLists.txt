set(HELLO_TRIANGLE_SHADERS 
	${CMAKE_SOURCE_DIR}/shaders/HelloTriangle/vertex.glsl 
	${CMAKE_SOURCE_DIR}/shaders/HelloTriangle/fragment.glsl)
set(TEXTURE_SHADERS
	${CMAKE_SOURCE_DIR}/shaders/Textures/vertex.glsl
	${CMAKE_SOURCE_DIR}/shaders/Textures/fragment.glsl)

set(SOURCES_LIST
	main.cpp 
	HelloTriangle.h 
	Textures.h
	SDLContext.h 
	SDLContext.cpp
	Shader.h
	Shader.cpp
	${HELLO_TRIANGLE_SHADERS}
	${TEXTURE_SHADERS}
	)

add_executable(OpenGLTutorial ${SOURCES_LIST})

# Make filter for VS solution
source_group("Shaders\\HelloTriangle" FILES ${HELLO_TRIANGLE_SHADERS})
source_group("Shaders\\Textures" FILES ${TEXTURE_SHADERS})

find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

find_path(STB_INCLUDE_DIR NAMES stb.h PATH_SUFFIXES stb)
include_directories(${STB_INCLUDE_DIR})

target_link_libraries(OpenGLTutorial PRIVATE SDL2::SDL2 SDL2::SDL2main glad::glad)