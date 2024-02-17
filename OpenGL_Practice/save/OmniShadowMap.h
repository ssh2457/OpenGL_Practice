#pragma once

#include "ShadowMap.h"

class OmniShadowMap : public ShadowMap {
public:
	OmniShadowMap();
	virtual ~OmniShadowMap();

	virtual bool Init(GLuint width, GLuint height) override;

	virtual void Write() override;

	virtual void Read(GLenum TextureUnit) override;
private:
};