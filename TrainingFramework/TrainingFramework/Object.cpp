#include "stdafx.h"
#include "Object.h"
#include "Vertex.h"


Object::Object()
{

}

Object::~Object()
{
	delete m_model;
	delete m_texture;
	delete m_shader;
}

bool Object::Load(char* modelPath, char* texturePath, char* VSpath, char* FSpath)
{
	m_model = new Model(modelPath);
	m_texture = new Texture();
	m_shader = new Shaders();
	m_model->LoadModel(modelPath);
	m_texture->LoadTexture(texturePath);
	m_shader->Init(VSpath, FSpath);
	camera = new Camera();
	return true;
}

void Object::CleanUp()
{
	glDeleteBuffers(1, &this->m_model->m_vboId);
	glDeleteBuffers(1, &(this->m_model->m_iboId));
	glDeleteTextures(1, &this->m_texture->m_TextureId);

}

void Object::Draw() {
	glUseProgram(m_shader -> program);
	glEnable(GL_DEPTH_TEST);

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