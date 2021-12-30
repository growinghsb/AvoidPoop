#pragma once

#include "CObj.h"

class CEnemy :
    public CObj
{
public:
    CEnemy(wstring tag, FPOINT pos, POINT size, class Texture* texture, class ObjLayer* layer, float speed, int maxHp);
    virtual ~CEnemy() = default;

    void init()   override;
    void update() override;
    void render(HDC backDC) override;
    bool collision() override;

    void changeSpeed(const float speed)
    {
        mSpeed = speed;
    }

    void decreaseHp(const int offencePower) 
    {
        mMaxHp -= offencePower;
    }

    int getMaxHp() 
    {
        return mMaxHp;
    }

    bool isDie() 
    {
        return mMaxHp <= 0;
    }

private:
    class ObjLayer* mLayer;
    float mSpeed;
    float mSpeedWeight;
    int mMaxHp;
};

