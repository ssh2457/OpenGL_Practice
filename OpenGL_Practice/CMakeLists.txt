# CMakeList.txt : CMake project for OpenGL_Practice, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (OpenGL_Practice 
			"main.cpp"
"Camera.h" "Camera.cpp"
"CommonValues.h" 
"DirectionalLight.h" "DirectionalLight.cpp" 
"Light.h" "Light.cpp" 
"Material.h" "Material.cpp" 
"Mesh.h" "Mesh.cpp"
"Model.h" "Model.cpp" 
"OmniShadowMap.h" "OmniShadowMap.cpp"
"PointLight.h" "PointLight.cpp" 
"Shader.h" "Shader.cpp"
"ShadowMap.h" "ShadowMap.cpp"
"SpotLight.h" "SpotLight.cpp"
"Texture.h" "Texture.cpp"
"Window.h" "Window.cpp" 
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGL_Practice PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.


target_link_libraries(${CMAKE_PROJECT_NAME}
glfw
libglew_static
assimp
)