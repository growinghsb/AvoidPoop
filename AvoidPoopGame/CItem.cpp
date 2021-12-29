#include "CItem.h"
#include "CObj.h"

CItem::CItem(wstring tag, FPOINT pos, POINT size, Texture* texture)
	: CObj(tag, pos, size, texture)
{
}
