#pragma once

#include <GL/glew.h>


class Material {
public:
	Material();
	Material(GLfloat specularIntensity, GLfloat shininess);
	virtual ~Material();

	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);


private:
	GLfloat SpecularIntensity;
	GLfloat Shininess;
};