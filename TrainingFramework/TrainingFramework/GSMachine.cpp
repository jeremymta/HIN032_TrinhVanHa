#include "stdafx.h"
#include "GSMachine.h"

GSMachine::GSMachine()
{
}

GSMachine::~GSMachine()
{
}

void GSMachine::ChangeState(std::shared_ptr<GSBase> state)
{
	this->m_NextState = state;
}

void GSMachine::ChangeState(StateType type)
{
	ChangeState(CreateGameState(type));
}

void GSMachine::PushState(StateType type)
{
	if (!m_StateStack.empty())
	{
		m_StateStack.top()->Pause();
	}
	std::shared_ptr<GSBase> newGS = CreateGameState(type);
	m_StateStack.push(newGS);
	m_NextState = newGS;
}

void GSMachine::PopState()
{
	if (m_ActiveState != nullptr)
	{
		m_ActiveState->Exit();
		m_StateStack.pop();
		m_StateStack.top()->Resume();
	}
}

void GSMachine::PerformStateChange()
{
	if (m_NextState != nullptr)
	{
		m_StateStack.push(m_NextState);
		m_NextState->Init();
		m_ActiveState = m_NextState;
		m_NextState = nullptr;
	}
}

std::shared_ptr<GSBase> GSMachine::GetCurrentState() const
{
	return m_ActiveState;
}

std::shared_ptr<GSBase> GSMachine::CreateGameState(StateType type)
{
	switch (type)
	{
	case StateType::GS_INTRO:
	{
		return std::make_shared<GSIntro>();
	}
	break;
	default:
		break;
	}
	return std::shared_ptr<GSBase>();
}
