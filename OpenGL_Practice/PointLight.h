#pragma once
#include <vector>

#include "Light.h"
#include "OmniShadowMap.h"

class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat near, GLfloat far,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat con, GLfloat lin, GLfloat exp);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint positionLocation,
		GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

	std::vector<glm::mat4> CalculateLightTransform();

	glm::vec3 GetPosition();
	GLfloat GetFarPlane();

	~PointLight();

protected:
	glm::vec3 position;

	GLfloat constant, linear, exponent;
	GLfloat farPlane;
};

