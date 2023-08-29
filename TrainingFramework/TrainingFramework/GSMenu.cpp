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
	auto model = ResourcesManager::GetInstance()->getModel(1);
	auto shader = ResourcesManager::GetInstance()->getShader(0);
	auto texture = ResourcesManager::GetInstance()->getTexture(1);
	m_obj = std::make_shared<Object>(model, texture, shader);
	auto camera = SceneManager::GetInstance()->GetCamera();
	m_obj->AttachCamera(camera);
	m_obj->Set2DSize(50, 100);
	m_obj->SetPos({ 300, 500, 0 });
	m_obj->SetRotation(Vector3(0.0f, 3.14f, 3.14f));
	m_obj->SetScale(Vector3(1.0f, 1.0f, 1.0f));


}

void GSMenu::Exit()
{
	m_obj.reset();
}

void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}

void GSMenu::Update(float deltaTime)
{
	m_obj->Update(deltaTime);
	SceneManager::GetInstance()->Update(deltaTime);
}

void GSMenu::Draw()
{
	m_obj->Draw();
}

void GSMenu::HandleEvent()
{
}

void GSMenu::OnKey(unsigned char key, bool pressed)
{
	if (pressed)
	{
		switch (key)
		{
		case KEY_SPACE:
			m_key |= 1 << 0;
			break;
		case KEY_E:
			m_key |= 1 << 1;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_SPACE:
			m_key ^= 1 << 0;
			GSMachine::GetInstance()->PushState(StateType::GS_MENU);
			break;
		case KEY_E:
			m_key ^= 1 << 1;
			exit(0);
			//GSMachine::GetInstance()->Exit();
			break;
		default:
			break;
		}
	}
	SceneManager::GetInstance()->Key(key, pressed);
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
