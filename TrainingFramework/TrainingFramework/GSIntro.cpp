#include "stdafx.h"
#include "GSIntro.h"
#include "GSMachine.h"
#include "Globals.h"
#include "ResourcesManager.h"
#include "SceneManager.h"

GSIntro::~GSIntro()
{
}

void GSIntro::Init()
{
	m_time = 2.0f;
	m_key = 0;
	auto model = ResourcesManager::GetInstance()->getModel(0);
	auto shader = ResourcesManager::GetInstance()->getShader(0);
	auto texture = ResourcesManager::GetInstance()->getTexture(0);
	m_obj = std::make_shared<Object>(model, texture, shader);
	auto camera = SceneManager::GetInstance()->GetCamera();
	m_obj->AttachCamera(camera);
	m_obj->Set2DSize(100, 100);
	m_obj->SetPos({ 200, 200, 0 });

}

void GSIntro::Exit()
{
	m_obj.reset();
}

void GSIntro::Pause()
{
}

void GSIntro::Resume()
{
}

void GSIntro::Update(float deltaTime)
{
	m_time -= deltaTime;
	if (m_key & (1 << 0)) // space pressed
	{
		GSMachine::GetInstance()->PushState(StateType::GS_MENU);
	}
	
		m_obj->Update(deltaTime);
	
}

void GSIntro::Draw()
{
	m_obj->Draw();
	//SceneManager::GetInstance()->Draw();

}

void GSIntro::HandleEvent()
{
}

void GSIntro::OnKey(unsigned char key, bool pressed)
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
			GSMachine::GetInstance()->Exit();
			break;
		default:
			break;
		}
	}
	
}

void GSIntro::OnMouseClick(int x, int y, unsigned char key, bool pressed)
{
}

void GSIntro::OnMouseMove(int x, int y)
{
}

void GSIntro::OnMouseScroll(int x, int y, short delta)
{
}
