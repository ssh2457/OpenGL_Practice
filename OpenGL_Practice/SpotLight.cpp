#include "SpotLight.h"

SpotLight::SpotLight()
	: PointLight()
	, Direction(glm::vec3(0.f, 0.f, 0.f))
	, Edge(0)
	, ProcEdge(cosf(glm::radians(Edge))) {
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat ambientIntensity, GLfloat diffuseIntensity,
	GLfloat posX, GLfloat posY, GLfloat posZ,
	GLfloat dirX, GLfloat dirY, GLfloat dirZ,
	GLfloat con, GLfloat lin, GLfloat exp,
	GLfloat edge)
	: PointLight(red, green, blue, ambientIntensity, diffuseIntensity, posX, posY, posZ, con, lin, exp)
	, Direction(glm::normalize(glm::vec3(dirX, dirY, dirZ)))
	, Edge(edge)
	, ProcEdge(cosf(glm::radians(Edge))) {
}

SpotLight::~SpotLight()
{
}

void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint colourLocation, 
	GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation, 
	GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, 
	GLuint edgeLocation) {

	glUniform1f(ambientIntensityLocation, AmbientIntensity);
	glUniform3f(colourLocation, Colour.x, Colour.y, Colour.z);
	glUniform1f(diffuseIntensityLocation, DiffuseIntensity);

	glUniform3f(positionLocation, Position.x, Position.y, Position.z);
	glUniform1f(constantLocation, Constant);
	glUniform1f(linearLocation, Linear);
	glUniform1f(exponentLocation, Exponent);
	
	glUniform3f(directionLocation, Direction.x, Direction.y, Direction.z);
	glUniform1f(edgeLocation, ProcEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir) {
	Position = pos;
	Direction = dir;
}
