#pragma once
#include "Obj.h"

class Monster :
    public Obj
{
public:
    Monster(FPOINT pos, class Texture* texture, float speed, float scale, float regenTime, int hp);
    ~Monster() = default;

    virtual void init()             override;
    virtual void update()           override;
    virtual void render(HDC backDC) override;

    bool isValid();
    void changeSpeed(float speed)
    {
        mSpeed = speed;
    }

    float getRegenTime() const 
    {
        return mRegenTime;
    }

    int getHP() const
    {
        return mHP;
    }
    
    float getSpeed() const
    {
        return mSpeed;
    }

    void changeHP(int hp) 
    {
        mHP = hp;
    }

    bool isDie() 
    {
        return mHP <= 0;
    }

private:
    class Texture* mTexture;

    float mSpeed;
    float mScale;
    float mRegenTime;
    int mHP;
    COLOR mHPBarColor;
};

