#pragma once

#include "Common.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

struct UniformDirectionalLight {
	GLuint uniformColour;
	GLuint uniformAmbientIntensity;
	GLuint uniformDiffuseIntensity;
	GLuint uniformDirection;
};

struct UniformPointLight {
	GLuint uniformColour;
	GLuint uniformAmbientIntensity;
	GLuint uniformDiffuseIntensity;

	GLuint uniformPosition;
	GLuint uniformConstant;
	GLuint uniformLinear;
	GLuint uniformExponent;
};

struct UniformSpotLight {
	GLuint uniformColour;
	GLuint uniformAmbientIntensity;
	GLuint uniformDiffuseIntensity;

	GLuint uniformPosition;
	GLuint uniformConstant;
	GLuint uniformLinear;
	GLuint uniformExponent;

	GLuint uniformDirection;
	GLuint UniformEdge;
};


class Shader {
public:
	Shader();
	virtual ~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation() const;
	GLuint GetModelLocation() const;
	GLuint GetViewLocation() const;
	GLuint GetAmbientIntensityLocation() const;
	GLuint GetColourLocation() const;
	GLuint GetDiffuseIntensityLocation() const;
	GLuint GetDirectionLocation() const;
	GLuint GetSpecularIntensityLocation() const;
	GLuint GetShininessLocation() const;
	GLuint GetEyePositionLocation() const;

	void UseShader();
	void ClearShader();

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount);
private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
		uniformSpecularIntensity, uniformShininess,
		uniformPointLightCount, uniformSpotLightCount;

	int PointLightCount, spotLightCount;

	UniformDirectionalLight uniformDirectionalLight;
	UniformPointLight uniformPointLights[MAX_POINT_LIGHT];
	UniformSpotLight uniformSpotLights[MAX_SPOT_LIGHT];


	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
