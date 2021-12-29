#include "CItem.h"
#include "CObj.h"

CItem::CItem(wstring tag, FPOINT pos, POINT size, Texture* texture, ObjLayer* layer)
	: CObj(tag, pos, size, texture)
	, mLayer(layer)
{
}
