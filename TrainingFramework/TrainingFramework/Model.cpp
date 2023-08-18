#include "stdafx.h"
#include "Model.h"
#include "Vertex.h"
#include <cstdio>
#include <iostream>

Model::Model()
{
	//LoadModel(filename);
	numVertices = 0;
	numIndices = 0;

	m_vboId = 0;
	m_iboId = 0;
	m_numberOfVertices = 0;

}

Model::~Model()
{
	if (m_vboId != 0) {
		glDeleteTextures(1, &m_vboId);
	}
	if (m_iboId != 0) {
		glDeleteTextures(1, &m_iboId);
	}
}

GLint Model::LoadModel(const std::string& filename)
{
	FILE* fmodel;
	fopen_s(&fmodel, filename.c_str(), "r");
	// kiem tra file ton tai
	if (!fmodel)
	{
		std::cerr << "Couldn't open file: " << filename << "\n";
		return -1;
	}
	Vertex* vboData;
	GLint* iboData;

	fscanf_s(fmodel, "NrVertices: %d\n", &numVertices);
	vboData = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		fscanf(fmodel, "   %*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n", &vboData[i].pos.x, &vboData[i].pos.y, &vboData[i].pos.z, &vboData[i].uv.x, &vboData[i].uv.y);
		vboData[i].pos.y -= 1;
	}

	fscanf_s(fmodel, "NrIndices: %d\n", &numIndices);
	iboData = new int[numIndices];
	for (int i = 0; i < numIndices/3; i+=1)
	{
		fscanf_s(fmodel, "   %*d.    %d,    %d,    %d\n", &iboData[3*i], &iboData[3*i + 1], &iboData[3*i+ 2]);
	}

	

	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, vboData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * numIndices, iboData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return 0;
}

GLint Model::getNumberOfVertices()
{
	return m_numberOfVertices;
}