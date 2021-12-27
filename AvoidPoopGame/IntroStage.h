#pragma once
#include "Stage.h"

class IntroStage :
    public Stage
{
public:
    IntroStage(int order);
    ~IntroStage() = default;

    void init() override;
    void update() override;
    void render(HDC backDC) override;

    void stageClear() override
    {
    }

    virtual void enter() override;
    virtual void exit() override;
};

