#pragma once 

#include "Light.h"

class PointLight : public Light {
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat ambientIntensity, GLfloat diffuseIntensity,
		GLfloat x, GLfloat y, GLfloat z,
		GLfloat con, GLfloat lin, GLfloat exp);

	virtual ~PointLight();

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint positionLocation,
		GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);

private:
	glm::vec3 Position;
	GLfloat Constant, Linear, Exponent;

	// pointlight attenuation equation:
	// Exponent * x^2 + Linear * x + Constant
};
