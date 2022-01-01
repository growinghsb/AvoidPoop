#include "CItem.h"
#include "CObj.h"
#include "CPlayer.h"
#include "ObjLayer.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"

CItem::CItem(wstring tag, FPOINT pos, POINT size, Texture* texture, ObjLayer* layer,  int validTime, ITEM_LIST category)
	: CObj(tag, pos, size, texture)
	, mLayer(layer)
	, mSpeed(250)
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
	mPos.mY += mSpeed * DS;
}

bool CItem::collision()
{
	CPlayer& player = mLayer->getPlayer();
	
	if (COLLISION_REC(player.getPos(), player.getSize().x, mPos, mSize.x))
	{
		// 플레이어 한테 아이템 효과 적용 시킨 후 true 리턴
		switch (mCategory)
		{
		case ITEM_LIST::HP:
			player.increaseHp(10);
			break;

		case ITEM_LIST::MP:
			player.increaseMp(20);
			break;

		case ITEM_LIST::OFFENCE_POWER:
			player.bulletOffencePowerUp(1);
			break;

		case ITEM_LIST::BULLET_UP:
			player.bulletLevelUp();
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
	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}
