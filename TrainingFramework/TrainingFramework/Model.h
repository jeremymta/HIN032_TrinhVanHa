#pragma once
#include<string>
#include <GLES2/gl2.h>
class Model
{	
public:
	Model(char* filename);
	~Model();
	int LoadModel(char* filename);
	GLint getNumberOfVertices();

public:
	int numVertices, numIndices;

	GLuint m_vboId;
	GLuint m_iboId;
	GLint m_numberOfVertices;
};
