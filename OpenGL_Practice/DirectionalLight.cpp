#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
	: Light()
	, Direction(glm::vec3(0.f, -1.f, 0.f)) {

}


DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat x, GLfloat y, GLfloat z)
	: Light(red, green, blue, ambientIntensity, diffuseIntensity)
	, Direction(glm::vec3(x, y, z)) {

}

DirectionalLight::~DirectionalLight() {

}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation) {
	glUniform3f(ColourLocation, Colour.x, Colour.y, Colour.z);
	glUniform1f(ambientIntensityLocation, AmbientIntensity);

	glUniform3f(directionLocation, Direction.x, Direction.y, Direction.z);
	glUniform1f(diffuseIntensityLocation, DiffuseIntensity);
}