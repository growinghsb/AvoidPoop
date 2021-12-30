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

FPOINT CObj::getCenter() const
{
	return FPOINT{ float((mPos.mX + mSize.x) / 2), float((mPos.mY + mSize.y) / 2) };
}

int CObj::getRadius() const
{
	return mSize.x / 2;
}

POINT CObj::getSize() const
{
	return mSize;
}

const Texture& CObj::getTexture() const
{
	return *mTexture;
}
