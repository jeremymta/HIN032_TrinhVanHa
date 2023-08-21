#pragma once
#include "stdafx.h"
#include <vector>
#include "Camera.h"
#include "Object.h"
#include <fstream>

class SceneManager
{
private:
	std::vector<Object*>* m_Objects;
	std::shared_ptr<Camera> m_Camera;
	int KeyPress = 0;

public:
	std::shared_ptr<Camera> GetCamera() {
		return m_Camera;
	}
	SceneManager() = default;
	~SceneManager() {};
	static SceneManager* GetInstance();
	static SceneManager* s_Instance;

	bool Init(char* pathToSM);

	void Draw();
	void Update(float deltaTime);
	void Key(unsigned char key, bool bIsPressed);
	void CleanUp();

};

