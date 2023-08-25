#include "stdafx.h"
#include "GSMenu.h"
#include "Globals.h"
#include "ResourcesManager.h"
#include "SceneManager.h"
#include "GSMachine.h"

GSMenu::~GSMenu()
{
}

void GSMenu::Init()
{
	m_key = 0;
	m_mouse = 0;
	auto model = ResourcesManager::GetInstance()->getModel(0);
	auto shader = ResourcesManager::GetInstance()->getShader(0);
	auto texture = ResourcesManager::GetInstance()->getTexture(1);
	m_obj = std::make_shared<Object>(model, texture, shader);
	auto camera = SceneManager::GetInstance()->GetCamera();
	m_obj->AttachCamera(camera);
	m_obj->Set2DSize(600, 450);
}

void GSMenu::Exit()
{
}

void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}

void GSMenu::Update(float deltaTime)
{
}

void GSMenu::Draw()
{
}

void GSMenu::HandleEvent()
{
}

void GSMenu::OnKey(unsigned char key, bool pressed)
{
}

void GSMenu::OnMouseClick(int x, int y, unsigned char key, bool pressed)
{
}

void GSMenu::OnMouseMove(int x, int y)
{
}

void GSMenu::OnMouseScroll(int x, int y, short delta)
{
}
