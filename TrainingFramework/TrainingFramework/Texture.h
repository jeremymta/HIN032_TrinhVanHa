#pragma once
#include<string>
#include <GLES2/gl2.h>

class Texture
{
	public:
		Texture();
		~Texture();

		bool LoadTexture(char* filename);
	
		GLuint m_TextureId;
		




};
