#pragma once
#include <GL/glew.h>

#include "stb_image.h"

class Texture {
public:
	Texture() = delete;
	Texture(const char* fileLoc);
	virtual ~Texture();

	bool LoadTexture();
	bool LoadTextureA();

	void UseTexture();
	void ClearTexture();

private:
	GLuint textureID;
	int width, height, bitDepth;
	const char* fileLocation;
};
