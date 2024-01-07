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
						GLfloat posX, GLfloat posY, GLfloat posZ,
						GLfloat con, GLfloat lin, GLfloat exp)
	: Light(1024, 1024,
			red, green, blue, 
			ambientIntensity, diffuseIntensity)
	, Position(glm::vec3(posX, posY, posZ))
	, Constant(con)
	, Linear(lin)
	, Exponent(exp) {
}

PointLight::~PointLight() {
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint colourLocation,
							GLuint diffuseIntensityLocation, GLuint positionLocation,
							GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation) {
	glUniform1f(ambientIntensityLocation, AmbientIntensity);
	glUniform3f(colourLocation, Colour.x, Colour.y, Colour.z);
	glUniform1f(diffuseIntensityLocation, DiffuseIntensity);

	glUniform3f(positionLocation, Position.x, Position.y, Position.z);
	glUniform1f(constantLocation, Constant);
	glUniform1f(linearLocation, Linear);
	glUniform1f(exponentLocation, Exponent);
}
