#pragma once
#include <memory>
#include "GSBase.h"
#include "Object.h"

class GSMenu : public GSBase
{
public:
    using GSBase::GSBase;
    ~GSMenu() override;
    // Inherited via GSBase
    void Init() override;
    void Exit() override;
    void Pause() override;
    void Resume() override;
    void Update(float deltaTime) override;
    void Draw() override;

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