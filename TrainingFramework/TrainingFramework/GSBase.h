#pragma once
#include "stdafx.h"
#include <memory>
enum class StateType {
	GS_INVALID = 0,
	GS_INTRO,
	GS_MENU,
	GS_PLAY
};

class GSBase
{
public:

	GSBase() {};
	GSBase(StateType stateType);
	virtual ~GSBase();

	//virtual void
public:

	virtual void Init() = 0;
	virtual void Exit() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	StateType GetStateType();

	virtual void HandleEvent() = 0;
	virtual void OnKey(unsigned char key, bool pressed) = 0;
	virtual void OnMouseClick(int x, int y, unsigned char key, bool pressed) = 0;
	virtual void OnMouseMove(int x, int y) = 0;
	virtual void OnMouseScroll(int x, int y, short delta) = 0;

private:

	StateType m_StateType;


public:

	//StateType GetStateType();
	template<class T>
	std::shared_ptr<GSBase> CreateState();
};

//need to review later 
template<class T>
inline std::shared_ptr<GSBase> GSBase::CreateState()
{
	return  std::make_shared<T>();
}

