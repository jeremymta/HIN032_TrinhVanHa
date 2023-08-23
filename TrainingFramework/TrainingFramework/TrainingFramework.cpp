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
#include "SceneManager.h"
#include "Camera.h"

GLuint keyPressed = 0;
std::shared_ptr<Camera> myCamera;

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	ResourcesManager::Construct();
	ResourcesManager::GetInstance()->LoadResources("resources.data");
	
	SceneManager::GetInstance()->Init("../Resources/Manager/SceneManager.txt");
	
	return 0;
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SceneManager::GetInstance()->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

int KeyPressed = 0;
void Update(ESContext* esContext, float deltaTime)
{
	SceneManager::GetInstance()->Update(deltaTime);
	
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	SceneManager::GetInstance()->Key(key, bIsPressed);

}

void OnMouseClick(ESContext* esContext, GLint x, GLint y, unsigned char key, bool pressed)
{
	printf("MouseClick\n");
}

void OnMouseMove(ESContext* esContext, GLint x, GLint y)
{
	//printf("MouseMove\n");
}

void OnMouseScroll(ESContext* esContext, GLint x, GLint y, short delta)
{
	//printf("MouseScroll\n");
}

void CleanUp()
{
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

	esRegisterMouseButtonFunc(&esContext, OnMouseClick);
	esRegisterMouseScrollFunc(&esContext, OnMouseScroll);
	esRegisterMouseMoveFunc(&esContext, OnMouseMove);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

