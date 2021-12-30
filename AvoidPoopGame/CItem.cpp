#include "CItem.h"
#include "CObj.h"
#include "CPlayer.h"
#include "ObjLayer.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Texture.h"

CItem::CItem(wstring tag, FPOINT pos, POINT size, Texture* texture, ObjLayer* layer,  int validTime, ITEM_LIST category)
	: CObj(tag, pos, size, texture)
	, mLayer(layer)
	, mCreateTime(0)
	, mValidTime(validTime)
	, mCategory(category)
{
}

void CItem::init()
{
}

void CItem::update()
{
	mCreateTime += DS;
}

bool CItem::collision()
{
	CPlayer& player = mLayer->getPlayer();
	
	if (CollisionManager::getInstance()->ractangleVsRactangle(player.getPos(), player.getSize().x, mPos, mSize.x)) 
	{
		// 플레이어 한테 아이템 효과 적용 시킨 후 true 리턴
		switch (mCategory)
		{
		case ITEM_LIST::HP:
			player.increaseHp(5);
			break;
		case ITEM_LIST::MP:
			break;
		case ITEM_LIST::OFFENCE_POWER:
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}

void CItem::render(HDC backDC)
{
	POINT tRes = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, tRes.x, tRes.y, mTexture->getTextureDC(), 0, 0, tRes.x, tRes.y, COLOR_MAGENTA);
}
