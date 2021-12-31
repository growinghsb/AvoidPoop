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
			player.increaseMp(10);
			break;
		case ITEM_LIST::OFFENCE_POWER:
			player.bulletOffencePowerUp(1);
			break;

		case ITEM_LIST::BULLET1:
			player.changeBulletTexture(FIND_TEXTURE(L"bullet1"));
			break;

		case ITEM_LIST::BULLET2:
			player.changeBulletTexture(FIND_TEXTURE(L"bullet2"));
			break;

		case ITEM_LIST::BULLET3:
			player.changeBulletTexture(FIND_TEXTURE(L"bullet3"));
			break;

		case ITEM_LIST::MISSILE:
			player.missileCountUp();
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
