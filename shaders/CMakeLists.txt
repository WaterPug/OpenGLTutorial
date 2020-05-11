set(SHADER_FILES
	HelloTriangle/vertex.glsl 
	HelloTriangle/fragment.glsl
	Textures/vertex.glsl
	Textures/fragment.glsl)
	
foreach(shaderFile ${SHADER_FILES})
	configure_file(${shaderFile} ${CMAKE_CURRENT_BINARY_DIR}/${shaderFile} COPYONLY)
endforeach(shaderFile)