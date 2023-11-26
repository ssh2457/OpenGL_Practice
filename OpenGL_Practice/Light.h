#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light {
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity,
		GLfloat x, GLfloat y, GLfloat z, GLfloat diffuseIntensity);
	virtual ~Light();

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint directionLocation);

private:
	glm::vec3 Colour;
	GLfloat AmbientIntensity;

	glm::vec3 Direction;
	GLfloat DiffuseIntensity;
};