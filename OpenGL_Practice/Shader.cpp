#include "Shader.h"

Shader::Shader()
	:shaderID(0)
	, uniformProjection(0)
	, uniformModel(0)
	, uniformView(0)
	, uniformSpecularIntensity(0)
	, uniformShininess(0)
	, uniformEyePosition(0)
	, PointLightCount(0)
	, uniformPointLightCount(0) {
	memset(&uniformDirectionalLight, 0, sizeof(UniformDirectionalLight));
}

Shader::~Shader() {
	ClearShader();
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation) {
	std::string vectexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);

	CreateFromString(vectexString.c_str(), fragmentString.c_str());
}

std::string Shader::ReadFile(const char* fileLocation) {
	std::string content;
	std::ifstream fileStream (fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("failed to read %s! file doesn't exist.\n", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + '\n');
	}
	fileStream.close();

	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
	shaderID = glCreateProgram();
	if (!shaderID) {
		printf("Error Creating Shadder program!\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0, };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: %s\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: %s\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");
	for (int i = 0; i < MAX_POINT_LIGHT; ++i) {
		char locBuff[100] = { '\0', };

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", i);
		uniformPointLights[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLights[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLights[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		uniformPointLights[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		uniformPointLights[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		uniformPointLights[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		uniformPointLights[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);
	}

	uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");
	for (int i = 0; i < MAX_SPOT_LIGHT; ++i) {
		char locBuff[100] = { '\0', };

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.colour", i);
		uniformSpotLights[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
		uniformSpotLights[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		uniformSpotLights[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		uniformSpotLights[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
		uniformSpotLights[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
		uniformSpotLights[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
		uniformSpotLights[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		uniformSpotLights[i].uniformDirection = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		uniformSpotLights[i].UniformEdge = glGetUniformLocation(shaderID, locBuff);
	}
}

void Shader::SetDirectionalLight(DirectionalLight* dLight) {
	if (dLight == nullptr) {
		return;
	}

	dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour, 
					uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(PointLight* pLight, unsigned int lightCount)
{
	if (pLight == nullptr) {
		return;
	}

	if (lightCount > MAX_POINT_LIGHT) {
		lightCount = MAX_POINT_LIGHT;
	}

	glUniform1i(uniformPointLightCount, lightCount);
	for (int i = 0; i < lightCount; ++i) {
		pLight[i].UseLight(uniformPointLights[i].uniformAmbientIntensity,
							uniformPointLights[i].uniformColour,
							uniformPointLights[i].uniformDiffuseIntensity,
							uniformPointLights[i].uniformPosition,
							uniformPointLights[i].uniformConstant,
							uniformPointLights[i].uniformLinear,
							uniformPointLights[i].uniformExponent);
	}

}

void Shader::SetSpotLights(SpotLight* sLight, unsigned int lightCount) {
	if (sLight == nullptr) {
		return;
	}

	if (lightCount > MAX_SPOT_LIGHT) {
		lightCount = MAX_SPOT_LIGHT;
	}

	glUniform1i(uniformSpotLightCount, lightCount);
	for (int i = 0; i < lightCount; ++i) {
		sLight[i].UseLight(uniformSpotLights[i].uniformAmbientIntensity,
			uniformSpotLights[i].uniformColour,
			uniformSpotLights[i].uniformDiffuseIntensity,
			uniformSpotLights[i].uniformPosition,
			uniformSpotLights[i].uniformDirection,
			uniformSpotLights[i].uniformConstant,
			uniformSpotLights[i].uniformLinear,
			uniformSpotLights[i].uniformExponent,
			uniformSpotLights[i].UniformEdge);
	}
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0, };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: %s\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

GLuint Shader::GetProjectionLocation() const{
	return uniformProjection;
}

GLuint Shader::GetModelLocation() const {
	return uniformModel;
}

GLuint Shader::GetViewLocation() const {
	return uniformView;
}

GLuint Shader::GetAmbientIntensityLocation() const {
	return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetColourLocation() const {
	return uniformDirectionalLight.uniformColour;
}

GLuint Shader::GetDiffuseIntensityLocation() const {
	return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation() const {
	return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation() const {
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation() const {
	return uniformShininess;
}

GLuint Shader::GetEyePositionLocation() const {
	return uniformEyePosition;
}


void Shader::UseShader() {
	glUseProgram(shaderID);
}

void Shader::ClearShader() {
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;
	memset(&uniformDirectionalLight, 0, sizeof(UniformDirectionalLight));
}