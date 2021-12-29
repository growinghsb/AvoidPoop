#pragma once

#include "CObj.h"

class CItem :
    public CObj
{
public:
    CItem(wstring tag, FPOINT pos, POINT size, class Texture* texture);
    virtual ~CItem() = default;

private:
};

