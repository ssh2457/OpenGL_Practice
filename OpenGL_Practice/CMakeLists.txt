# CMakeList.txt : CMake project for OpenGL_Practice, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (OpenGL_Practice "OpenGL_Practice.cpp" "OpenGL_Practice.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGL_Practice PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
