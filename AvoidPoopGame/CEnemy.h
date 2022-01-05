#pragma once

#include "CObj.h"

class CEnemy :
    public CObj
{
public:
    CEnemy(wstring tag, FPOINT pos, POINT size, class Texture* texture, class ObjLayer* layer, float speed, int maxHp);
    virtual ~CEnemy();

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
    //void createBullet(); 나중에, 일단 구조적인 부분에 집중

    class ObjLayer* mLayer;
    float mSpeed;
    float mSpeedWeight;
    int mMaxHp;
    float mRelativeAngle;
    float mAbsoluteAngle;
    float mRotateX;
    float mRotateY;

    list<class CBullet*> mBullets;
};

