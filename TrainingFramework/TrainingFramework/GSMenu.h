#pragma once
#include "GSBase.h"
#include "Object.h"
class GSMenu :
    public GSBase
{
    // Inherited via GSBase
    virtual void Init() override;
    virtual void Exit() override;
    virtual void Pause() override;
    virtual void Resume() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void HandleEvent();
    void OnKey(unsigned char key, bool pressed) override;
    void OnMouseClick(int x, int y, unsigned char key, bool pressed) override;
    void OnMouseMove(int x, int y) override;
    void OnMouseScroll(int x, int y, short delta) override;

private:
    unsigned int m_key;
    unsigned int m_mouse;
    std::shared_ptr<Object> m_obj;
};