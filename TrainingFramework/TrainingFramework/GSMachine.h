#pragma once
#include "stdafx.h"

#include "GSBase.h"
#include "GSIntro.h"

#include <stack>
#include <memory>
class GSMachine
{
private:
	std::stack<std::shared_ptr<GSBase>> m_StateStack;
	std::shared_ptr<GSBase> m_ActiveState;
	std::shared_ptr<GSBase> m_NextState;

public:
	GSMachine();
	~GSMachine();

	void ChangeState(std::shared_ptr<GSBase> state);
	void ChangeState(StateType type);
	void PushState(StateType type);
	void PopState();
	void PerformStateChange();

	std::shared_ptr<GSBase> GetCurrentState() const;
	std::shared_ptr<GSBase> CreateGameState(StateType type);


};
