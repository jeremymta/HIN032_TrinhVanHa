#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "SceneManager.h"
#include "ResourcesManager.h"
#include "Globals.h"

int ParseElementType(const std::string& type);

void SceneManager::Init()
{
	m_init = true;
}

void SceneManager::CleanUp()
{
	for (auto& it : m_cameraList)
	{
		it.second.reset();
	}
	for (auto& it : m_objectList)
	{
		it.second.reset();
	}
	m_cameraList.clear();
	m_objectList.clear();
}


int ParseElementType(const std::string& type)
{
	if (type == "#Objects:")
		return ET_OBJECT;
	if (type == "#Cameras:")
		return ET_CAMERA;
	return ET_INVALID;
}
