#pragma once
#include<string>
#include <GLES2/gl2.h>

class Texture
{
	public:
		Texture();
		~Texture();
		void SetFilter(GLint filter);
		void SetWrap(GLint wrapMode);

		bool LoadTexture(char* filename);
	
		GLuint m_TextureId;
		
		GLuint getTextureId() { return m_TextureId; };


};
