#pragma once

#include "Light.h"
#include <GL/glew.h>
#include <glm/glm.hpp>


class DirectionalLight : public Light {
public:
	DirectionalLight();
	DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeightm,
					GLfloat red, GLfloat green, GLfloat blue,
					GLfloat ambientIntensity, GLfloat diffuseIntensity,
					GLfloat x, GLfloat y, GLfloat z);
	virtual ~DirectionalLight();

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint directionLocation);

	glm::mat4 CalcLightTransform();
private:
	glm::vec3 Direction;
};