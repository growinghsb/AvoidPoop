#include "CBullet.h"
#include "CObj.h"

CBullet::CBullet(wstring tag, FPOINT pos, POINT size, Texture* texture)
	: CObj(tag, pos, size, texture)
{
}
