#include "PointLight.h"

PointLight::PointLight()
	: Light()
	, Position(glm::vec3(0.f, 0.f, 0.f))
	, Constant(1.f)
	, Linear(0.f)
	, Exponent(0.f) {
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
						GLfloat ambientIntensity, GLfloat diffuseIntensity,
						GLfloat x, GLfloat y, GLfloat z,
						GLfloat con, GLfloat lin, GLfloat exp)
	: Light(red, green, blue, ambientIntensity, diffuseIntensity)
	, Position(glm::vec3(x, y, z))
	, Constant(con)
	, Linear(lin)
	, Exponent(exp) {
}

PointLight::~PointLight() {
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
							GLuint diffuseIntensityLocation, GLuint positionLocation,
							GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation) {
	glUniform1f(ambientIntensityLocation, AmbientIntensity);
	glUniform3f(ambientColourLocation, Colour.x, Colour.y, Colour.z);
	glUniform1f(diffuseIntensityLocation, DiffuseIntensity);
	glUniform3f(positionLocation, Position.x, Position.y, Position.z);
	glUniform1f(constantLocation, Constant);
	glUniform1f(linearLocation, Linear);
	glUniform1f(exponentLocation, Exponent);
}
