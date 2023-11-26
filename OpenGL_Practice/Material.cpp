#include "Material.h"


Material::Material()
	: SpecularIntensity(0.f)
	, Shininess(0.f) {

}

Material::Material(GLfloat specularIntensity, GLfloat shininess)
	: SpecularIntensity(specularIntensity)
	, Shininess(shininess) {

}

Material::~Material() {

}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation) {
	glUniform1f(specularIntensityLocation, SpecularIntensity);
	glUniform1f(shininessLocation, Shininess);
}