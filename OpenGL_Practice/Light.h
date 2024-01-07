#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShadowMap.h"

class Light {
public:
	Light();
	Light(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue, 
		GLfloat ambientIntensity,GLfloat diffuseIntensity);
	virtual ~Light();

	// Shadow
	ShadowMap* GetShadowMap() const { return shadowMap; }

protected:
	glm::vec3 Colour;
	GLfloat AmbientIntensity;
	GLfloat DiffuseIntensity;

	// Shadow
	ShadowMap* shadowMap;
	glm::mat4 lightProj;
};
