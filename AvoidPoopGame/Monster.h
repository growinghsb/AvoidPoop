#pragma once
#include "Obj.h"

class Monster :
    public Obj
{
public:
    Monster(FPOINT pos, int size, float speed, float scale);
    ~Monster() = default;

    virtual void init() override;
    virtual void update() override;
    virtual void render(HDC backDC) override;

    bool isValid();
    void changePos(FPOINT pos) 
    {
        mPos = pos;
    }

    void changeSize(int size) 
    {
        mSize = size;
    }
    
    void changeSpeed(float speed)
    {
        mSpeed = speed;
    }

private:
    float mSpeed;
    float mScale;
};

