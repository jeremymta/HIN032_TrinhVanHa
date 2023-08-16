#include "stdafx.h"
#include "Texture.h"
#include "../Utilities/TGA.h"


Texture::Texture()
{
	m_TextureId = 0;

}
Texture::~Texture()
{
	if (m_TextureId != 0) {
		glDeleteTextures(1, &m_TextureId);
	}
}

bool Texture::LoadTexture(char* filename)
{
	//Generate the texture
	glGenTextures(1, &m_TextureId);

	// Bind and load Texture data.
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	int iWidth, iHeight, iBpp;
	char* imageData = LoadTGA(filename, &iWidth, &iHeight, &iBpp);
	if (imageData && iBpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else if (imageData && iBpp == 32) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	else {
		return true;
	}

	//Setting texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[]imageData;
	return false;
}


