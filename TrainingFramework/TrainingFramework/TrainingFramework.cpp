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
#include "GSMachine.h"

GLuint keyPressed = 0;
std::shared_ptr<Camera> myCamera;

bool running;

int Init(ESContext* esContext)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	ResourcesManager::Construct();
	ResourcesManager::GetInstance()->LoadResources("resources.data");
	
	SceneManager::GetInstance()->Init("../Resources/Manager/SceneManager.txt");

	GSMachine::Construct();
	GSMachine::GetInstance()->Init();
	GSMachine::GetInstance()->PushState(StateType::GS_INTRO);

	return 0;
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//SceneManager::GetInstance()->Draw();

	if (running)
	{
		GSMachine::GetInstance()->GetCurrentState()->Draw();
	}

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

int KeyPressed = 0;
void Update(ESContext* esContext, float deltaTime)
{
	//SceneManager::GetInstance()->Update(deltaTime);
	running = GSMachine::GetInstance()->IsRunning();
	esContext->running = running;
	if (running)
	{
		GSMachine::GetInstance()->GetCurrentState()->Update(deltaTime);
	}
	GSMachine::GetInstance()->ChangeState();
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	//SceneManager::GetInstance()->Key(key, bIsPressed);
	if (running)
	{
		GSMachine::GetInstance()->GetCurrentState()->OnKey(key, bIsPressed);
	}

}

void OnMouseClick(ESContext* esContext, GLint x, GLint y, unsigned char key, bool pressed)
{
	printf("MouseClick\n");
	if (running)
	{
		GSMachine::GetInstance()->GetCurrentState()->OnMouseClick(x, y, key, pressed);
	}
}

void OnMouseMove(ESContext* esContext, GLint x, GLint y)
{
	//printf("MouseMove\n");
	if (running)
	{
		GSMachine::GetInstance()->GetCurrentState()->OnMouseMove(x, y);
	}
}

void OnMouseScroll(ESContext* esContext, GLint x, GLint y, short delta)
{
	//printf("MouseScroll\n");
	if (running)
	{
		GSMachine::GetInstance()->GetCurrentState()->OnMouseScroll(x, y, delta);
	}
}

void CleanUp()
{
	ResourcesManager::GetInstance()->CleanUp();
	SceneManager::GetInstance()->CleanUp();
	ResourcesManager::DestroyInstance();
	SceneManager::GetInstance();
	GSMachine::GetInstance()->CleanUp();
	GSMachine::DestroyInstance();

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

