# CMakeList.txt : CMake project for OpenGL_Practice, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (OpenGL_Practice OpenGL_Practice.cpp Camera.cpp Mesh.cpp Shader.cpp Texture.cpp Window.cpp "Light.h" "Light.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGL_Practice PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.


target_link_libraries(${CMAKE_PROJECT_NAME}
glfw
libglew_static
)