#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
	: Light()
	, Direction(glm::vec3(0.f, -1.f, 0.f)) {

}


DirectionalLight::DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeightm, 
								GLfloat red, GLfloat green, GLfloat blue, 
								GLfloat ambientIntensity, GLfloat diffuseIntensity, 
								GLfloat x, GLfloat y, GLfloat z)
	: Light(shadowWidth, shadowHeightm, 
			red, green, blue, 
			ambientIntensity, diffuseIntensity)
	, Direction(glm::vec3(x, y, z)) {
	lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

DirectionalLight::~DirectionalLight() {

}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation) {
	glUniform3f(ColourLocation, Colour.x, Colour.y, Colour.z);
	glUniform1f(ambientIntensityLocation, AmbientIntensity);

	glUniform3f(directionLocation, Direction.x, Direction.y, Direction.z);
	glUniform1f(diffuseIntensityLocation, DiffuseIntensity);
}

glm::mat4 DirectionalLight::CalcLightTransform()
{
	return lightProj * glm::lookAt(-Direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
