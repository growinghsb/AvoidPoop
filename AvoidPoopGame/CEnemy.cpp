#include "CEnemy.h"
#include "CBullet.h"
#include "Texture.h"
#include "TimeManager.h"
#include "CPlayer.h"
#include "ObjLayer.h"
#include "CollisionManager.h"
#include "Core.h"
#include "ResourceManager.h"

CEnemy::CEnemy(wstring tag, FPOINT pos, POINT size, Texture* texture, ObjLayer* layer, float speed, int maxHp)
	: CObj(tag, pos, size, texture)
	, mLayer(layer)
	, mSpeed(speed)
	, mSpeedWeight(1.0f)
	, mMaxHp(maxHp)
	, mRelativeAngle(0.f)
	, mAbsoluteAngle(0.f)
	, mRotateX(0.f)
	, mRotateY(0.f)
{
}

CEnemy::~CEnemy()
{
	for (auto item : mBullets)
	{
		delete item;
	}
	mBullets.clear();
}

void CEnemy::init()
{
}

void CEnemy::update()
{
	static float bulletRegen = 0.f;
	bulletRegen += DS;

	if (mTag == L"enemy")
	{
		// 플레이어 좌표 받아와서 플레이어에 대한 각도 업데이트
		FPOINT pPos = mLayer->getPlayer().getPos();

		float x = pPos.mX - mPos.mX;
		float y = pPos.mY - mPos.mY;

		float radian = atan2f(y, x);
		float degree = radian * 180 / PI;

		mRelativeAngle = degree - 90.f;
		mAbsoluteAngle = 270.f + mRelativeAngle;

		if (bulletRegen > 1.0f) 
		{
			createBullet();
			bulletRegen = 0.f;
		}	
	}

	for (auto item : mBullets)
	{
		item->update();
	}

	mPos.mY += (mSpeed * DS) * mSpeedWeight;
}

void CEnemy::render(HDC backDC)
{
	SelectObject(backDC, GetStockObject(DC_BRUSH));

	int hpBarY = (int)mPos.mY - 15;
	SetDCBrushColor(backDC, COLOR_RED);

	POINT res = mTexture->getResolution();

	if (mTag == L"enemy")
	{
		static HDC hTempMemDC = nullptr;
		HBITMAP hTempBitmap, hOldBitmap;

		if (nullptr == hTempMemDC)
		{
			hTempMemDC = CreateCompatibleDC(Core::getInstance()->getDC());
		}

		hTempBitmap = GetRotatedBitmap(Core::getInstance()->getDC(), mTexture->getTextureDC(), mTexture->getTextureBitmap(), res.x + 10, res.y + 10, mRelativeAngle, COLOR_WINDOW + 1);
		hOldBitmap = (HBITMAP)SelectObject(hTempMemDC, hTempBitmap);
		DeleteObject(hOldBitmap);

		mRotateX = float(-(res.x / 2));
		mRotateY = float(-(res.y / 2));

		TransparentBlt(backDC, int(mPos.mX + mRotateX), int(mPos.mY + mRotateY), res.x, res.y, hTempMemDC, 0, 0, res.x, res.y, COLOR_WHITE);
		Rectangle(backDC, int(mPos.mX + mRotateX), int(hpBarY + mRotateY), int(mPos.mX + mMaxHp + mRotateX), int(hpBarY + 5 + mRotateY)); // Hp Bar

		DeleteObject(hTempBitmap);

		for (auto item : mBullets)
		{
			item->render(backDC);
		}
	}
	else
	{
		TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
		Rectangle(backDC, (int)mPos.mX, hpBarY, (int)mPos.mX + mMaxHp, hpBarY + 5); // Hp Bar
	}
	SetDCBrushColor(backDC, COLOR_WHITE); // 다시 흰색으로 변경
}

bool CEnemy::collision()
{
	return false;
}

void CEnemy::createBullet()
{
	Texture* texture = FIND_TEXTURE(L"bullet0");
	POINT res = texture->getResolution();

	FPOINT gunPos{mPos.mX + cosf(mAbsoluteAngle), mPos.mY + sinf(mAbsoluteAngle)};
	float bulletPosX = gunPos.mX + mRotateX;
	float bulletPosY = gunPos.mY;

	mBullets.push_back(new CBullet(L"eBullet", FPOINT{ bulletPosX, bulletPosY }, res, texture, mLayer, mPos, 1.5f, 3, mAbsoluteAngle));
	
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	while (iter != endIter) 
	{
		if (!(*iter)->isValid())
		{
			delete (*iter);
			iter = mBullets.erase(iter);
			endIter = mBullets.end();
		}
		else 
		{
			++iter;
		}
	}
}
