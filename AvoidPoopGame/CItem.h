#pragma once

#include "CObj.h"

class CItem :
    public CObj
{
public:
    CItem(wstring tag, FPOINT pos, POINT size, class Texture* texture, class ObjLayer* layer);
    virtual ~CItem() = default;

private:
    class ObjLayer* mLayer;
};

