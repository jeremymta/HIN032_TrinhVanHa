#pragma once
#include "stdafx.h"
#include "Singleton.h"
#include "GSBase.h"
#include <stack>
#include <memory>

class GSMachine final : public SingletonDclp<GSMachine>
{
public:
	void Init();
	void CleanUp();
	void PushState(StateType stateType);
	void PopState();
	//void ChangeState(std::shared_ptr<GSBase> state);
	//void ChangeState(StateType type);
	void ChangeState();
	void Exit();
	void PerformStateChange();

	std::shared_ptr<GSBase> GetCurrentState() const;
	//std::shared_ptr<GSBase> CreateGameState(StateType type);
	inline bool IsRunning() { return m_running; };

private:
	std::stack<std::shared_ptr<GSBase>> m_pStateStack;
	std::shared_ptr<GSBase> m_pActiveState;
	std::shared_ptr<GSBase> m_pNextState;
	bool m_running;
};
