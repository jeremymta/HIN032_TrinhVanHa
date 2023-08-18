#pragma once
#include<string>
#include <GLES2/gl2.h>
#include "../Utilities/Math.h"

class Model
{	
public:
	Model();
	~Model();

	GLint LoadModel(const std::string& filename);
	GLint getNumberOfVertices();

	GLint numVertices, numIndices;

	GLuint m_vboId;
	GLuint m_iboId;
	GLint m_numberOfVertices;

	GLuint getVBOid() { return m_vboId; };
	GLuint getIBOid() { return m_iboId; };
};
