#include "CObj.h"

CObj::CObj(wstring tag, FPOINT pos, POINT size, Texture* texture)
	: mTag(tag)
	, mPos(pos)
	, mSize(size)
	, mTexture(texture)
{
}

const wstring& CObj::getTag() const
{
	return mTag;
}

FPOINT CObj::getPos() const
{
	return mPos;
}

POINT CObj::getSize() const
{
	return mSize;
}

const Texture& CObj::getTexture() const
{
	return *mTexture;
}
