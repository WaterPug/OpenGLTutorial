set(HELLO_TRIANGLE_SHADERS Shaders/HelloTriangle/vertex.glsl Shaders/HelloTriangle/fragment.glsl)

set(SOURCES_LIST
	main.cpp 
	HelloTriangle.h 
	SDLContext.h 
	SDLContext.cpp
	Shader.h
	Shader.cpp
	${HELLO_TRIANGLE_SHADERS}
	)

add_executable(OpenGLTutorial ${SOURCES_LIST})

# Make filter for VS solution
source_group("Shaders" FILES ${HELLO_TRIANGLE_SHADERS})

find_package(glad CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(OpenGLTutorial PRIVATE SDL2::SDL2 SDL2::SDL2main glad::glad)

# Softlink in bin folder
foreach(shaderFile ${HELLO_TRIANGLE_SHADERS})
	configure_file(${shaderFile} ${CMAKE_CURRENT_BINARY_DIR}/${shaderFile} COPYONLY)
endforeach(shaderFile)