#pragma once
#include<string>
#include <GLES2/gl2.h>

class Model
{	
public:
	Model();
	~Model();

	int LoadModel(char* filename);
	GLint getNumberOfVertices();

	int numVertices, numIndices;

	GLuint m_vboId;
	GLuint m_iboId;
	GLint m_numberOfVertices;

	GLuint getVBOid() { return m_vboId; };
	GLuint getIBOid() { return m_iboId; };
};
