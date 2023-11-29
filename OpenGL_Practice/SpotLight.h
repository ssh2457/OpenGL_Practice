#pragma once

#include "PointLight.h"

class SpotLight : public PointLight {
public:
	SpotLight();
	SpotLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat ambientIntensity, GLfloat diffuseIntensity,
		GLfloat posX, GLfloat posY, GLfloat posZ,
		GLfloat dirX, GLfloat dirY, GLfloat dirZ,
		GLfloat con, GLfloat lin, GLfloat exp,
		GLfloat edge);

	virtual ~SpotLight();

	void UseLight(GLuint ambientIntensityLocation, GLuint colourLocation,
		GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
		GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
		GLuint edgeLocation);

	void SetFlash(glm::vec3 pos, glm::vec3 dir);

private:
	glm::vec3 Direction;
	GLfloat Edge, ProcEdge;
};