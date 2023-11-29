#pragma once 

#include "Light.h"

class PointLight : public Light {
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat ambientIntensity, GLfloat diffuseIntensity,
		GLfloat posX, GLfloat posY, GLfloat posZ,
		GLfloat con, GLfloat lin, GLfloat exp);

	virtual ~PointLight();

	void UseLight(GLuint ambientIntensityLocation, GLuint colourLocation,
		GLuint diffuseIntensityLocation, GLuint positionLocation,
		GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

protected:
	glm::vec3 Position;
	GLfloat Constant, Linear, Exponent;

	// pointlight attenuation equation:
	// Exponent * x^2 + Linear * x + Constant
};
