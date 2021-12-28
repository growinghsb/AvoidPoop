#include "Gun.h"
#include "Bullet.h"
#include "StageManager.h"
#include "PlayStage.h"
#include "Player.h"

Gun::Gun(Player* palyer, float bulletSpeed)
	: mPlayer(palyer)
	, mBulletSpeed(bulletSpeed)
	, mBulletScale(1.f)
	, mBulletOffensePower(3)
	, mBulletSize(20)
	, mBulletColor(COLOR{ 0, 255,0 })
{
}

Gun::~Gun()
{
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	while (iter != endIter)
	{
		delete (*iter);
		iter = mBullets.erase(iter);
		endIter = mBullets.end();
	}
}

void Gun::update()
{
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	while (iter != endIter)
	{
		(*iter)->update();

		// �Ѿ� �ϳ��� ���ؼ� ���Ϳ��� �浹üũ
		PlayStage* playStage = (PlayStage*)StageManager::getInstance()->getCurrentStage();
		if (playStage->crushMonsterRemove(*(*iter)))
		{
			// ���Ϳ� �浹 �����Ƿ� �Ѿ� �����
			delete (*iter);
			iter = mBullets.erase(iter);
			endIter = mBullets.end();
		}
		else
		{
			// �浹 �ȵ�
			++iter;
		}
	}
}

void Gun::render(HDC backDC)
{
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	SelectObject(backDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(backDC, RGB(mBulletColor.r, mBulletColor.g, mBulletColor.b));
	for (; iter != endIter; ++iter)
	{
		(*iter)->render(backDC);
	}
	SetDCBrushColor(backDC, COLOR_WHITE);
}

void Gun::createBullet()
{
	float bulletPosX = float(mPlayer->getPos().mX + mPlayer->getSize() / 3);
	float bulletPosY = float(mPlayer->getPos().mY);

	if (mBullets.empty())
	{
		mBullets.push_back(new Bullet(FPOINT{ bulletPosX ,bulletPosY }, mBulletSize, mBulletSpeed, mBulletScale, mBulletOffensePower));
	}
	else
	{
		if (mBullets.front()->isValid())
		{
			mBullets.push_back(new Bullet(FPOINT{ bulletPosX ,bulletPosY }, mBulletSize, mBulletSpeed, mBulletScale, mBulletOffensePower));
		}
		else
		{
			Bullet* invalidBullet = mBullets.front();
			mBullets.pop_front();

			invalidBullet->changePos(FPOINT{ bulletPosX ,bulletPosY });
			mBullets.push_back(invalidBullet);
		}
	}
}

void Gun::bulletScaleUp()
{
	if ((int)mBulletScale < 2)
	{
		mBulletScale += 0.1f;
	}
	else
	{
		mBulletScale = 1.9f;
	}
	setBulletScale();
}

void Gun::bulletScaleDown()
{
	if ((int)mBulletScale >= 1)
	{
		mBulletScale -= 0.1f;
	}
	else
	{
		mBulletScale = 1.0f;
	}
	setBulletScale();
}

void Gun::setBulletScale()
{
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	while (iter != endIter)
	{
		(*iter)->setScale(mBulletScale);
		++iter;
	}
}