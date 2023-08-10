#include "stdafx.h"
#include "Object.h"
#include "Vertex.h"


Object::Object()
{
}

Object::~Object()
{

}

bool Object::Load(char* modelPath, char* texturePath) 
{

	m_model =  new Model(modelPath);
	m_model->LoadModel(modelPath);
	m_texture =  new Texture();
	m_texture -> LoadTexture(texturePath);
	m_shader = new Shaders();
	return m_shader -> Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Object::Draw() {
	glEnable(GL_DEPTH_TEST);
	glUseProgram(m_shader -> program);


	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	glBindTexture(GL_TEXTURE_2D, m_texture->m_TextureId);
	//glEnable(GL_DEPTH_TEST);

	//Thiet lap vertex attribute pointer cho vi tri
	if (m_shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader->positionAttribute);
		glVertexAttribPointer(m_shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	// Thiet lap cho Texture 
	if (m_shader->iTextCoordLoc != -1)
	{
		glEnableVertexAttribArray(m_shader->iTextCoordLoc);
		glVertexAttribPointer(m_shader->iTextCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3));
	}

	if (m_shader->iTextureLoc != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_shader->iTextureLoc, 0);
	}

	glDrawElements(GL_TRIANGLES, m_model->numIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}