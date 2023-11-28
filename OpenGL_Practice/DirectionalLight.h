#pragma once

#include "Light.h"
#include <GL/glew.h>
#include <glm/glm.hpp>


class DirectionalLight : public Light {
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity,
		GLfloat x, GLfloat y, GLfloat z, GLfloat diffuseIntensity);
	virtual ~DirectionalLight();

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint directionLocation);
private:
	glm::vec3 Direction;
};