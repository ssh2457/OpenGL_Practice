#include "Light.h"

Light::Light()
	: Colour(glm::vec3(1.f, 1.f, 1.f))
	, AmbientIntensity(1.f)
	, DiffuseIntensity(0.f) {

}


Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity)
	: Colour(glm::vec3(red, green, blue))
	, AmbientIntensity(ambientIntensity)
	, DiffuseIntensity(diffuseIntensity){

}

Light::~Light() {

}