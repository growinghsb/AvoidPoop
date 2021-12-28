#pragma once

#include "Game.h"

class CResource
{
public:
	CResource(wstring tag);
	virtual ~CResource() = default;

	virtual bool load() = 0;

protected:
	wstring mResourceTag;
};

