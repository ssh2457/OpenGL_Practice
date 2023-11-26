#include "Light.h"

Light::Light()
	: Colour(glm::vec3(1.f, 1.f, 1.f))
	, AmbientIntensity(1.f)
	, Direction(glm::vec3(0.f, -1.f, 0.f))
	, DiffuseIntensity(0.f) {

}


Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat x, GLfloat y, GLfloat z, GLfloat diffuseIntensity)
	: Colour(glm::vec3(red, green, blue))
	, AmbientIntensity(ambientIntensity)
	, Direction(glm::vec3(x, y, z))
	, DiffuseIntensity(diffuseIntensity){

}

Light::~Light() {

}

void Light::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation) {
	glUniform3f(ambientColourLocation, Colour.x, Colour.y, Colour.z);
	glUniform1f(ambientIntensityLocation, AmbientIntensity);

	glUniform3f(directionLocation, Direction.x, Direction.y, Direction.z);
	glUniform1f(diffuseIntensityLocation, DiffuseIntensity);
}