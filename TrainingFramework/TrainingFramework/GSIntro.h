#pragma once
#include "GSBase.h"
#include <memory>
#include "Texture.h"
#include "Camera.h"
#include "Shaders.h"
#include "Model.h"
#include "Object.h"

class GSIntro : public GSBase
{

public:
	// Inherited via GSBase
	virtual void Init() override;
	virtual void Exit() override;
	virtual void Pause() override;
	virtual void Resume() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void HandleEvent() override;
	void OnKey(unsigned char key, bool pressed) override;
	void OnMouseClick(int x, int y, unsigned char key, bool pressed) override;
	void OnMouseMove(int x, int y) override;
	void OnMouseScroll(int x, int y, short delta) override;

private:
	float m_time;
	std::shared_ptr<Object> m_obj;
	std::shared_ptr<Camera> m_camera;
	unsigned char m_key;
};