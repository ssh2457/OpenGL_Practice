#include "Light.h"

Light::Light()
	: Colour(glm::vec3(1.f, 1.f, 1.f))
	, AmbientIntensity(1.f)
{

}


Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity)
	: Colour(glm::vec3(red, green, blue))
	, AmbientIntensity(ambientIntensity)
{

}

Light::~Light() {

}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation) {
	glUniform3f(ambientColourLocation, Colour.x, Colour.y, Colour.z);
	glUniform1f(ambientIntensityLocation, AmbientIntensity);
}