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
    void collision() override;

    void changeSpeed(const float speed)
    {
        mSpeed = speed;
    }

    void changeMaxHp(const int hp) 
    {
        mMaxHp = hp;
    }

private:
    void bulletCollision();

    class ObjLayer* mLayer;
    float mSpeed;
    float mSpeedWeight;
    int mMaxHp;
};

