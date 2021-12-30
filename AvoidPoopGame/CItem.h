#pragma once

#include "CObj.h"

class CItem :
    public CObj
{
public:
    CItem(wstring tag, FPOINT pos, POINT size, class Texture* texture, class ObjLayer* layer, int validTime, ITEM_LIST category);
    virtual ~CItem() = default;

    virtual void init();
    virtual void update();
    virtual bool collision();
    virtual void render(HDC backDC);

    bool isValidTime() 
    {
        return mCreateTime < mValidTime;
    }

private:
    class ObjLayer* mLayer;
    float mCreateTime; // 생성시간
    int mValidTime; // 유효시간
    ITEM_LIST mCategory; // 아이템 종류
};

