// TrainingFramework.cpp : Defines the entry point for the console application.
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

//GLuint vboId;
//GLuint iboId;
//GLuint textureID;
//Shaders myShaders;

//Model* model = new Model("../Resources/Models/Woman1.nfg");;
//Object obj;

//std::shared_ptr<Object> myObject = std::make_shared<Object>();
Object* myObject;

GLuint keyPressed;
std::shared_ptr<Camera> myCamera;


int Init ( ESContext *esContext )
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	myObject = new Object("../Resources/Models/Woman1.nfg", "../Resources/Textures/Woman1.tga",
		"../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
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

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	myObject->Draw();
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
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

int KeyPressed = 0;
void Update ( ESContext *esContext, float deltaTime )
{
	myObject->Update(deltaTime);
	if (KeyPressed & 1)
	{
		myObject->Move(deltaTime);
	}
	if (KeyPressed & (1 << 1)) 
	{
		myObject->camera->Move(Camera_Movement::RIGHT, deltaTime);
	}
	if (KeyPressed & (1 << 2))
	{
		myObject->camera->Move(FORWARD, deltaTime);
	}
	if (KeyPressed & (1 << 3))
	{
		myObject->camera->Move(BACKWARD, deltaTime);
	}
	if (KeyPressed & (1 << 4)) {
		myObject->camera->RotateCounterClockWise(yAxis, deltaTime);
	}
	if (KeyPressed & (1 << 5)) {
		myObject->camera->RotateClockWise(yAxis, deltaTime);
	}
	if (KeyPressed & (1 << 6)) {
		myObject->camera->RotateCounterClockWise(xAxis, deltaTime);
	}
	if (KeyPressed & (1 << 7)) {
		myObject->camera->RotateClockWise(xAxis, deltaTime);
	}

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_LEFT:
			KeyPressed |= 1;
			break;
		case KEY_RIGHT:
			KeyPressed |= 1 << 1;
			break;
			// Tuong tu voi cac phim con lai, neu co 8 phim thi cuoi cung se la KeyPressed |= 1 << 7;
		case KEY_UP:
			KeyPressed |= 1 << 2;
			break;
		case KEY_DOWN:
			KeyPressed |= 1 << 3;
			break;
		case KEY_MOVE_LEFT:
			KeyPressed |= 1 << 4;
			break;
		case KEY_MOVE_RIGHT:
			KeyPressed |= 1 << 5;
			break;
		case KEY_MOVE_FORWARD:
			KeyPressed |= 1 << 6;
			break;
		case KEY_MOVE_BACKWORD:
			KeyPressed |= 1 << 7;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_LEFT:
			KeyPressed ^= 1;
			break;
		case KEY_RIGHT:
			KeyPressed ^= 1 << 1;
			break;
		case KEY_UP:
			KeyPressed ^= 1 << 2;
			break;
		case KEY_DOWN:
			KeyPressed ^= 1 << 3;
			break;
		case KEY_MOVE_LEFT:
			KeyPressed ^= 1 << 4;
			break;
		case KEY_MOVE_RIGHT:
			KeyPressed ^= 1 << 5;
			break;
		case KEY_MOVE_FORWARD:
			KeyPressed ^= 1 << 6;
			break;
		case KEY_MOVE_BACKWORD:
			KeyPressed ^= 1 << 7;
			break;
		default:
			break;
		}
	}
}

void CleanUp()
{
	//glDeleteBuffers(1, &obj.m_model->m_vboId);
	//glDeleteBuffers(1, &obj.m_model->m_iboId);
	myObject->CleanUp();

}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

