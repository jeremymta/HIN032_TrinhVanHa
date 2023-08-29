#include "stdafx.h"
#include "Texture.h"
#include "../Utilities/TGA.h"
#include<iostream>
#include <algorithm>
#include "../Utilities/PNG.h"

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
	// check if file exist
	FILE* f;
	fopen_s(&f, filename.c_str(), "r");
	if (!f)
	{
		std::cerr << "Couldn't open file: " << filename << "\n";
		return -1;
	}
	std::cout << "Open " << filename << "\n";
	fclose(f);

	// check file extension
	size_t dotPos = filename.find_last_of('.');
	if (dotPos == std::string::npos)
	{
		std::cerr << "File type not supported\n";
		return -2;
	}

	//Generate the texture
	glGenTextures(1, &m_TextureId);
	// Bind and load Texture data.
	glBindTexture(GL_TEXTURE_2D, m_TextureId);

	GLint iWidth, iHeight, iBpp;

	// load pixel data
	char* pixelData = nullptr;
	std::string ext = filename.substr(dotPos + 1);
	std::transform(ext.begin(), ext.end(), ext.begin(), [](GLubyte c) {
		return std::tolower(c);
		});

	if (ext == "png")
	{
		// TODO: PNG load
		pixelData = LoadPNG(filename, &iWidth, &iHeight, &iBpp);
	}
	else if (ext == "tga")
	{
		pixelData = LoadTGA(filename.c_str(), &iWidth, &iHeight, &iBpp);
	}
	else
	{
		std::cerr << "File type not supported\n";
		return -2;
	}

	//char* imageData = LoadTGA(filename.c_str(), &iWidth, &iHeight, &iBpp);

	if (pixelData && iBpp == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
	}
	else if (pixelData && iBpp == 32) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
	}
	else {
		return true;
	}

	//Setting texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	// clean up
	glBindTexture(GL_TEXTURE_2D, 0);
	if (ext == "tga") delete pixelData;
	if (ext == "png") free(pixelData);

	return false;
}


