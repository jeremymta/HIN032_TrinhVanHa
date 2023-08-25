#include "stdafx.h"
#include "GSBase.h"

GSBase::GSBase()
{

}

GSBase::GSBase(StateType stateType)
{
	m_StateType = stateType;
}

GSBase::~GSBase()
{

}

StateType GSBase::GetStateType()
{
	return m_StateType;
}