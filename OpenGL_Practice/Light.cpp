#include "Light.h"

Light::Light()
	: Colour(glm::vec3(1.f, 1.f, 1.f))
	, AmbientIntensity(1.f)
	, DiffuseIntensity(0.f) {

}


Light::Light(GLfloat shadowWidth, GLfloat shadowHeightm,
			GLfloat red, GLfloat green, GLfloat blue,
	GLfloat ambientIntensity, GLfloat diffuseIntensity)
	: Colour(glm::vec3(red, green, blue))
	, AmbientIntensity(ambientIntensity)
	, DiffuseIntensity(diffuseIntensity)
	, shadowMap(new ShadowMap()) {
	shadowMap->Init(shadowWidth, shadowHeightm);
}

Light::~Light() {

}