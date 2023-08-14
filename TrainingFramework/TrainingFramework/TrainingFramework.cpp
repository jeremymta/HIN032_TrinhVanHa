// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Model.h"
#include "Texture.h"
#include "Object.h"

//GLuint vboId;
//GLuint iboId;
//GLuint textureID;
//Shaders myShaders;

//Model* model = new Model("../Resources/Models/Woman1.nfg");;
Object obj;

int Init ( ESContext *esContext )
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	obj.Load("../Resources/Models/Woman1.nfg", "../Resources/Textures/Woman1.tga", 
			"../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
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
	obj.Draw();
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

int KeyPressed = 0;
void Update ( ESContext *esContext, float deltaTime )
{
	obj.Update(deltaTime);
	if (KeyPressed & 1)
	{
		obj.Move(deltaTime);
	}
	if (KeyPressed & (1 << 1)) 
	{
		obj.camera->Move(Camera_Movement::RIGHT, deltaTime);
	}
	if (KeyPressed & (1 << 2))
	{
		obj.camera->Move(FORWARD, deltaTime);
	}
	if (KeyPressed & (1 << 3))
	{
		obj.camera->Move(BACKWARD, deltaTime);
	}
	if (KeyPressed & (1 << 4)) {
		obj.camera->RotateCounterClockWise(yAxis, deltaTime);
	}
	if (KeyPressed & (1 << 5)) {
		obj.camera->RotateClockWise(yAxis, deltaTime);
	}
	if (KeyPressed & (1 << 6)) {
		obj.camera->RotateCounterClockWise(xAxis, deltaTime);
	}
	if (KeyPressed & (1 << 7)) {
		obj.camera->RotateClockWise(xAxis, deltaTime);
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
	obj.CleanUp();

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

