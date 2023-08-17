#include "stdafx.h"
#include "Object.h"
#include "Vertex.h"

Object::Object(char* modelPath, char* texturePath, char* VSpath, char* FSpath)
{
	m_model = new Model();
	m_texture = new Texture();
	m_shader = new Shaders();
	m_model->LoadModel(modelPath);
	m_texture->LoadTexture(texturePath);
	m_shader->Init(VSpath, FSpath);

	float PI = 3.14;
	camera = new Camera(0.1f, 500.f, PI / 4.f);

	model.SetIdentity();
	//model.Display();
	WVP = model * camera->GetViewMatrix() * camera->GetPerspectiveMatrix();

}
Object::Object(Model* model, Texture* texture, Shaders* shader)
{
	m_model = model;
	m_texture = texture;
	m_shader = shader;

	float PI = 3.14;
	m_Camera = new Camera(0.1f, 500.f, PI / 4);

	//model.SetRotationY(PI / 2);
	this->model.SetIdentity();
	this->model = Matrix().SetScale(5, 2, 2) * Matrix().SetRotationY(PI) * Matrix().SetTranslation(1, 0, 0);

	//WVP = this->model * m_Camera->GetViewMatrix() * m_Camera->GetPerspectiveMatrix();
}

Object::~Object()
{
	delete m_model;
	delete m_texture;
	delete m_shader;
	delete camera;
}

/*
bool Object::Load(char* modelPath, char* texturePath, char* VSpath, char* FSpath)
{
	m_model = new Model();
	m_texture = new Texture();
	m_shader = new Shaders();
	m_model->LoadModel(modelPath);
	m_texture->LoadTexture(texturePath);
	m_shader->Init(VSpath, FSpath);

	camera = new Camera();
	float PI = 3.14;
	model.SetIdentity();
	//model.Display();
	WVP = model * camera->GetViewMatrix() * camera->GetPerspectiveMatrix();

	return true;
}
*/

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

	/*Vector3 deltaMove = (camera->m_cameraTarget - camera->m_cameraPos).Normalize() * deltaTime * camera->m_MoveSpeed;
	camera->m_cameraPos += deltaMove;
	camera->m_cameraTarget += deltaMove;*/

	//camera->m_cameraTarget.Display();

	/*camera->RotateCounterClockWise(Camera_Rotate::xAxis, deltaTime * camera->m_RotateSpeed);
	camera->UpdateCameraVector();*/
	camera->UpdateCameraVector();
	WVP = model * camera->GetViewMatrix() * camera->GetPerspectiveMatrix();
}

void Object::Move(float deltaTime)
{
	float velocity = moveSpeed * deltaTime;
	model = model * Matrix().SetTranslation(-velocity, 0, 0);
	//model.Display();
}


void Object::SetCamera(Camera* camera)
{
	this->m_Camera = camera;
}

void Object::SetModelMatrix(Vector3 scale, Vector3 rotation, Vector3 position)
{
	model = Matrix().SetScale(scale) * Matrix().SetRotationZ(rotation[2]) * Matrix().SetRotationX(rotation[0]) * Matrix().SetRotationY(rotation[1]) * Matrix().SetTranslation(position);
}