#include "stdafx.h"
#include "GSMachine.h"
#include "GSIntro.h"
#include "GSMenu.h"

std::shared_ptr<GSBase> CreateState(StateType stateType);

void GSMachine::Init()
{
	m_pActiveState = nullptr;
	m_pNextState = nullptr;
	m_running = true;
}

void GSMachine::CleanUp()
{
	m_pActiveState.reset();
	m_pNextState.reset();
	m_pActiveState = m_pNextState = nullptr;
}

//void GSMachine::ChangeState(std::shared_ptr<GSBase> state)
//{
//	this->m_pNextState = state;
//}
//
//void GSMachine::ChangeState(StateType type)
//{
//	ChangeState(CreateGameState(type));
//}

void GSMachine::ChangeState()
{
	if (m_pNextState)
	{
		m_pActiveState->Pause();
		m_pActiveState = m_pNextState;
		m_pActiveState->Init();
		m_pNextState = nullptr;
	}
	if (!m_running)
	{
		while (!m_pStateStack.empty())
		{
			auto state = m_pStateStack.top();
			state->Exit();
			state = nullptr;
			m_pStateStack.pop();
		}
	}
}

void GSMachine::Exit()
{
	m_running = false;
}

void GSMachine::PushState(StateType stateType)
{
	std::shared_ptr<GSBase> state = CreateState(stateType);
	if (m_pStateStack.empty()) // is first state
	{
		m_pStateStack.push(state);
		m_pActiveState = state;
		m_pActiveState->Init();
	}
	else
	{
		m_pStateStack.push(state);
		m_pNextState = state;
	}
}

void GSMachine::PopState()
{
	if (m_pActiveState != nullptr)
	{
		m_pActiveState->Exit();
		m_pStateStack.pop();
		m_pStateStack.top()->Resume();
	}
}

void GSMachine::PerformStateChange()
{
	if (m_pNextState != nullptr)
	{
		m_pStateStack.push(m_pNextState);
		m_pNextState->Init();
		m_pActiveState = m_pNextState;
		m_pNextState = nullptr;
	}
}

std::shared_ptr<GSBase> GSMachine::GetCurrentState() const
{
	return m_pActiveState;
}

/*
std::shared_ptr<GSBase> GSMachine::CreateGameState(StateType type)
{
	switch (type)
	{
	case StateType::GS_INTRO:
	{
		return std::make_shared<GSIntro>();
	}
	case StateType::GS_MENU:
	{
		return std::make_shared<GSMenu>();
	}
	break;
	default:
		break;
	}
	return std::shared_ptr<GSBase>();
}
*/

std::shared_ptr<GSBase> CreateState(StateType stateType)
{
	std::shared_ptr<GSBase> state = nullptr;
	switch (stateType)
	{
	case StateType::GS_INTRO:
		state = std::make_shared<GSIntro>(stateType);
		break;
	case StateType::GS_MENU:
		state = std::make_shared<GSMenu>(stateType);
		break;
	default:
		break;
	}
	return state;
}