﻿// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <conio.h>
#include <vector>
#include <iostream>
#include <Windows.h>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Model.h"
#include "Texture.h"
#include "Object.h"
#include "ResourcesManager.h"
#include "SceneManager.h"
#include "Camera.h"


//GLuint vboId;
//GLuint iboId;
//GLuint textureID;
//Shaders myShaders;

//std::shared_ptr<Object> myObject;

GLuint keyPressed = 0;
std::shared_ptr<Camera> myCamera;

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	//myObject = std::make_shared<Object>("../Resources/Models/Woman2.nfg", "../Resources/Textures/Woman2.tga",
	//	"../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

	ResourcesManager::Construct();
	//ResourcesManager::GetInstance()->Init();
	ResourcesManager::GetInstance()->LoadResources("resources.data");
	
	//std::shared_ptr<Model> model = std::make_shared<Model>();
	////model->LoadModel("../Resources/Models/Woman1.nfg");
	//model = ResourcesManager::GetInstance()->getModel(0);

	//std::shared_ptr<Shaders> shader = std::make_shared<Shaders>();
	////shader->Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	//shader = ResourcesManager::GetInstance()->getShader(0);

	//std::shared_ptr <Texture> texture = std::make_shared<Texture>();
	////texture->LoadTexture("../Resources/Textures/Woman1.tga");
	//texture = ResourcesManager::GetInstance()->getTexture(0);

	//myObject = std::make_shared<Object>(model, texture, shader);
	

	SceneManager::GetInstance()->Init("../Resources/Manager/SceneManager.txt");
	
	/*
	myObject->Load("../Resources/Models/Woman1.nfg", "../Resources/Textures/Woman1.tga",
			"../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	*/
	//model = new Model("../Resources/Models/Woman1.nfg");
	//texture = new Texture;
	//texture->LoadTexture("../Resources/Textures/Woman1.tga");

	////triangle data (heap)
	//Vertex verticesData[]{
	//	// pos               //textCoord
	//	{{-0.5f,0.5f,0.f},  {0.f,1.0f}},
	//	{{-0.5f,-0.5f,0.f}, {0.f,0.f}},
	//	{{0.5f,-0.5f,0.f},  {1.f,0.f}},
	//	{{0.5f,0.5f,0.f},  {1.f,1.f}}
	//};
	//unsigned int indices[] = { 0,1,2, 0, 2, 3};

	//buffer object
	//glGenBuffers(1, &vboId);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glGenBuffers(1, &iboId);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Generate the texture
	//glGenTextures(1, &textureID);

	// Bind and load Texture data.
	//glBindTexture(GL_TEXTURE_2D, textureID);
	//int iWidth, iHeight, iBpp;
	//char* imageData = LoadTGA("../Resources/Textures/Woman1.tga", &iWidth, &iHeight, &iBpp);
	//if (imageData && iBpp == 24) {
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	//}
	//else if (imageData && iBpp == 32) {
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	//}
	//else {
	//	return 0;
	//}

	////Setting texture parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glBindTexture(GL_TEXTURE_2D, 0);

	//creation of shaders and program 
	return 0;

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//myObject->Draw();

	SceneManager::GetInstance()->Draw();

	////Bind VBO
	//glBindBuffer(GL_ARRAY_BUFFER, m_model->m_vboId);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->m_iboId);
	//glBindTexture(GL_TEXTURE_2D, m_texture->m_TextureId);
	////glEnable(GL_DEPTH_TEST);

	////Thiet lap vertex attribute pointer cho vi tri
	//if (m_shader->positionAttribute != -1)
	//{
	//	glEnableVertexAttribArray(m_shader->positionAttribute);
	//	glVertexAttribPointer(m_shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//}

	//// Thiet lap cho Texture 
	//if (m_shader->iTextCoordLoc != -1)
	//{
	//	glEnableVertexAttribArray(m_shader->iTextCoordLoc);
	//	glVertexAttribPointer(m_shader->iTextCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3));
	//}

	//if (m_shader->iTextureLoc != -1)
	//{
	//	glActiveTexture(GL_TEXTURE0);
	//	glUniform1i(m_shader->iTextureLoc, 0);
	//}

	//if (m_shader->WVP_Mat != -1) {
	//	glUniformMatrix4fv(m_shader->WVP_Mat, 1, GL_FALSE, (float*)&WVP);
	//}

	//glDrawElements(GL_TRIANGLES, m_model->numIndices, GL_UNSIGNED_INT, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

int KeyPressed = 0;
void Update(ESContext* esContext, float deltaTime)
{
	SceneManager::GetInstance()->Update(deltaTime);
	//std::shared_ptr<Camera> camera = SceneManager::GetInstance()->GetCamera();

	
	//myObject->Update(deltaTime);

	//if (KeyPressed & 1)
	//{
	//	myObject->Move(deltaTime);
	//}
	//if (KeyPressed & 1) {
	//	//obj->Move(deltaTime);
	//	myObject->m_Camera->Move(Camera_Movement::LEFT, deltaTime);
	//}
	//if (KeyPressed & (1 << 1)) {
	//	myObject->m_Camera->Move(Camera_Movement::RIGHT, deltaTime);
	//}
	//if (KeyPressed & (1 << 2))
	//{
	//	myObject->m_Camera->Move(FORWARD, deltaTime);
	//}
	//if (KeyPressed & (1 << 3))
	//{
	//	myObject->m_Camera->Move(BACKWARD, deltaTime);
	//}
	//if (KeyPressed & (1 << 4)) {
	//	myObject->m_Camera->RotateCounterClockWise(yAxis, deltaTime);
	//}
	//if (KeyPressed & (1 << 5)) {
	//	myObject->m_Camera->RotateClockWise(yAxis, deltaTime);
	//}
	//if (KeyPressed & (1 << 6)) {
	//	myObject->m_Camera->RotateCounterClockWise(xAxis, deltaTime);
	//}
	//if (KeyPressed & (1 << 7)) {
	//	myObject->m_Camera->RotateClockWise(xAxis, deltaTime);
	//}
	
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	SceneManager::GetInstance()->Key(key, bIsPressed);

	
	//if (bIsPressed)
	//{
	//	switch (key)
	//	{
	//	case KEY_LEFT:
	//		KeyPressed |= 1;
	//		break;
	//	case KEY_RIGHT:
	//		KeyPressed |= 1 << 1;
	//		break;
	//		// Tuong tu voi cac phim con lai, neu co 8 phim thi cuoi cung se la KeyPressed |= 1 << 7;
	//	case KEY_UP:
	//		KeyPressed |= 1 << 2;
	//		break;
	//	case KEY_DOWN:
	//		KeyPressed |= 1 << 3;
	//		break;
	//	case KEY_MOVE_LEFT:
	//		KeyPressed |= 1 << 4;
	//		break;
	//	case KEY_MOVE_RIGHT:
	//		KeyPressed |= 1 << 5;
	//		break;
	//	case KEY_MOVE_FORWARD:
	//		KeyPressed |= 1 << 6;
	//		break;
	//	case KEY_MOVE_BACKWORD:
	//		KeyPressed |= 1 << 7;
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//else
	//{
	//	switch (key)
	//	{
	//	case KEY_LEFT:
	//		KeyPressed ^= 1;
	//		break;
	//	case KEY_RIGHT:
	//		KeyPressed ^= 1 << 1;
	//		break;
	//	case KEY_UP:
	//		KeyPressed ^= 1 << 2;
	//		break;
	//	case KEY_DOWN:
	//		KeyPressed ^= 1 << 3;
	//		break;
	//	case KEY_MOVE_LEFT:
	//		KeyPressed ^= 1 << 4;
	//		break;
	//	case KEY_MOVE_RIGHT:
	//		KeyPressed ^= 1 << 5;
	//		break;
	//	case KEY_MOVE_FORWARD:
	//		KeyPressed ^= 1 << 6;
	//		break;
	//	case KEY_MOVE_BACKWORD:
	//		KeyPressed ^= 1 << 7;
	//		break;
	//	default:
	//		break;
	//	}
	//}
	//
}

void CleanUp()
{
	//glDeleteBuffers(1, &obj.m_model->m_vboId);
	//glDeleteBuffers(1, &obj.m_model->m_iboId);
	//myObject->CleanUp();

	ResourcesManager::GetInstance()->CleanUp();
	SceneManager::GetInstance()->CleanUp();
	ResourcesManager::DestroyInstance();
	SceneManager::GetInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

