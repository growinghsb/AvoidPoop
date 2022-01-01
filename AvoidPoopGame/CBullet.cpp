#include "CBullet.h"
#include "CObj.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ObjLayer.h"
#include "CollisionManager.h"
#include "CEnemy.h"

CBullet::CBullet(wstring tag, FPOINT pos, POINT size, Texture* texture, ObjLayer* layer, float speedWeight, int offencePower)
	: CObj(tag, pos, size, texture)
	, mLayer(layer)
	, mSpeed(450.0f)
	, mSpeedWeight(speedWeight)
	, mOffencePower(offencePower)
{
}

void CBullet::init()
{
}

void CBullet::update()
{
	mPos.mY -= (mSpeed * DS) * mSpeedWeight;
}

void CBullet::render(HDC backDC)
{
	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}

bool CBullet::collision()
{
	list<CEnemy*>& objs = (list<CEnemy*>&)mLayer->getObstacle();

	auto iter = objs.begin();
	auto endIter = objs.end();

	while (iter != endIter)
	{
		if ((*iter)->getTag() == L"obstacle" && COLLISION_REC((*iter)->getPos(), (*iter)->getSize().x, mPos, mSize.x))
		{
			CEnemy* enemy = (CEnemy*)(*iter);
			enemy->decreaseHp(mOffencePower);

			if (enemy->isDie())
			{
				// 몬스터 죽으면 해당 포지션에 아이템 생성
				if (0 == rand() % 4)
				{
					mLayer->createItem((*iter)->getPos());
				}

				delete (*iter);
				objs.erase(iter);
			}
			return true;
		}
		else
		{
			++iter;
		}
	}
	return false;
}
