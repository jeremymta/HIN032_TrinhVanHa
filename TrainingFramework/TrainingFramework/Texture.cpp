#include "stdafx.h"
#include "Texture.h"
#include "../Utilities/TGA.h"
#include<iostream>


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

void Texture::SetFilter(GLint filter)
{
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	switch (filter)
	{
	case GL_NEAREST:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		break;
	case GL_LINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		break;
	default:
		std::cout << "Invalid filter mode\n";
		break;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetWrap(GLint wrapMode)
{
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	switch (wrapMode)
	{
	case GL_CLAMP_TO_EDGE:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		break;
	case GL_REPEAT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		break;
	default:
		std::cout << "Invalid wrap mode\n";
		break;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::LoadTexture(const std::string& filename)
{
	//Generate the texture
	glGenTextures(1, &m_TextureId);

	// Bind and load Texture data.
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	GLint iWidth, iHeight, iBpp;
	char* imageData = LoadTGA(filename.c_str(), &iWidth, &iHeight, &iBpp);
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


