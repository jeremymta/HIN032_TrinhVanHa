#include "stdafx.h"
#include "Object.h"
#include "Vertex.h"
#include <memory>

//Object::Object(char* modelPath, char* texturePath, char* VSpath, char* FSpath)
//{
//}

Object::Object(Model* model, Texture* texture, Shaders* shader)
{
		float PI = 3.14;
		this->worldMatrix.SetIdentity();
		this->worldMatrix = Matrix().SetScale(5, 2, 2) * Matrix().SetRotationY(PI) * Matrix().SetTranslation(1, 0, 0);
	
		WVP = this->worldMatrix * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();
}

Object::Object(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shaders> shader)
{
	m_model = model;
	m_texture = texture;
	m_shader = shader;

	float PI = 3.14;
	m_Camera = std::make_shared<Camera>(0.1f, 500.f, PI / 4);

	//model.SetRotationY(PI / 2);
	this->worldMatrix.SetIdentity();
	this->worldMatrix = Matrix().SetScale(5, 2, 2) * Matrix().SetRotationY(PI) * Matrix().SetTranslation(1, 0, 0);
}

Object::~Object()
{

}

void Object::CleanUp()
{
	glDeleteBuffers(1, &this->m_model->m_vboId);
	glDeleteBuffers(1, &(this->m_model->m_iboId));
	glDeleteTextures(1, &this->m_texture->m_TextureId);
}

void Object::Draw() {
	glUseProgram(m_shader->program);
	glEnable(GL_DEPTH_TEST);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	glBindTexture(GL_TEXTURE_2D, m_texture->m_TextureId);

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

	if (m_shader->WVP_Mat != -1) {
		glUniformMatrix4fv(m_shader->WVP_Mat, 1, GL_FALSE, (float*)&WVP);
	}

	glDrawElements(GL_TRIANGLES, m_model->numIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Object::Update(float deltaTime)
{
	m_Camera->UpdateCameraVector();
	WVP = worldMatrix * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();
}

void Object::Move(float deltaTime)
{
	float velocity = moveSpeed * deltaTime;
	worldMatrix = worldMatrix * Matrix().SetTranslation(-velocity, 0, 0);
}

void Object::SetCamera(std::shared_ptr<Camera> camera)
{
	this->m_Camera = camera;
	m_Camera->UpdateCameraVector();
	WVP = worldMatrix * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();
}

void Object::SetModelMatrix(Vector3 scale, Vector3 rotation, Vector3 position)
{
	worldMatrix = Matrix().SetScale(scale) * Matrix().SetRotationZ(rotation[2]) * Matrix().SetRotationX(rotation[0]) * Matrix().SetRotationY(rotation[1]) * Matrix().SetTranslation(position);
	WVP = worldMatrix * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();
}

void Object::SetRotation(Vector3 rotation)
{
	m_rotation = rotation;
	m_changed = true;
	worldMatrix = Matrix().SetRotationZ(rotation.z) * Matrix().SetRotationX(rotation.x) * Matrix().SetRotationY(rotation.y) * worldMatrix;
	WVP = worldMatrix * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();
}

void Object::SetScale(Vector3 scale)
{
	m_scale = scale;
	m_changed = true;
	worldMatrix = Matrix().SetScale(scale) * worldMatrix;
	WVP = worldMatrix * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();
}

void Object::SetPos(Vector3 pos)
{
	m_pos = pos;
	m_translation = pos;
	worldMatrix =  worldMatrix * Matrix().SetTranslation(pos);
	m_changed = true;
	WVP = worldMatrix * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();
}

void Object::AttachCamera(std::shared_ptr<Camera> camera)
{
	m_Camera = camera;
	m_changed = true;
	WVP = worldMatrix * m_Camera->GetViewMatrix() * m_Camera->GetProjectionMatrix();
}

void Object::Set2DSize(int x, int y)
{
	auto scale = Vector3(x, y, 1.0f);
	SetScale(scale);
}
