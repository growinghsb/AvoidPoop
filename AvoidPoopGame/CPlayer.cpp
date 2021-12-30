#include "CPlayer.h"
#include "CEnemy.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Core.h"
#include "Texture.h"
#include "CBullet.h"
#include "ResourceManager.h"
#include "ObjLayer.h"
#include "CollisionManager.h"
#include "StageManager.h"

CPlayer::CPlayer(wstring tag, FPOINT pos, POINT size, Texture* texture, ObjLayer* layer, float speed)
	: CObj(tag, pos, size, texture)
	, mLayer(layer)
	, mSpeed(speed)
	, mSpeedWeight(1.0f)
	, mCurrentHp(100)
	, mMaxHp(100)
	, mCurrentMp(100)
	, mMaxMp(100)
	, mCLaunchMode(true)
	, mBulletSpeedWeight(1.0f)
	, mBulletOffencePower(3)
{
}

CPlayer::~CPlayer()
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

void CPlayer::init()
{
}

void CPlayer::update()
{
	// Ű �Է� �̵� ó��
	if (ISPRESS(KEY_LIST::LEFT))
	{
		if ((int)mPos.mX > 0)
		{
			mPos.mX -= (mSpeed * DS) * mSpeedWeight;
		}
		else
		{
			mPos.mX = 0.f;
		}
	}

	if (ISPRESS(KEY_LIST::TOP))
	{
		if (mPos.mY > 0)
		{
			mPos.mY -= (mSpeed * DS) * mSpeedWeight;
		}
		else
		{
			mPos.mY = 0.f;
		}
	}

	if (ISPRESS(KEY_LIST::RIGHT))
	{
		if ((int)mPos.mX + mSize.x < WINDOW.right)
		{
			mPos.mX += (mSpeed * DS) * mSpeedWeight;
		}
		else
		{
			mPos.mX = (float)WINDOW.right - (float)mSize.x;
		}
	}

	if (ISPRESS(KEY_LIST::BOTTOM))
	{
		if ((int)mPos.mY + mSize.x < WINDOW.bottom)
		{
			mPos.mY += (mSpeed * DS) * mSpeedWeight;
		}
		else
		{
			mPos.mY = (float)WINDOW.bottom - (float)mSize.x;
		}
	}

	if (ISTIC(KEY_LIST::_1))
	{
		if ((int)mSpeedWeight < 2)
		{
			mSpeedWeight += 0.1f;
		}
		else
		{
			mSpeedWeight = 2.0f;
		}
	}

	if (ISTIC(KEY_LIST::_2))
	{
		if ((int)mSpeedWeight >= 1)
		{
			mSpeedWeight -= 0.1f;
		}
		else
		{
			mSpeedWeight = 1.0f;
		}
	}

	if (ISTIC(KEY_LIST::_3))
	{
		mBulletSpeedWeight += 0.1f;

		if (mBulletSpeedWeight > 2.0f)
		{
			mBulletSpeedWeight = 2.0f;
		}

		// �Ѿ� �ӵ� ����
		changeBulletWeight();
	}

	if (ISTIC(KEY_LIST::_4))
	{
		mBulletSpeedWeight -= 0.1f;

		if (mBulletSpeedWeight < 1.0f)
		{
			mBulletSpeedWeight = 1.0f;
		}

		// �Ѿ� �ӵ� ����
		changeBulletWeight();
	}

	if (ISTIC(KEY_LIST::LSHIFT))
	{
		mCLaunchMode ? mCLaunchMode = false : mCLaunchMode = true;
	}

	// ������
	if (mCLaunchMode)
	{
		if (ISTIC(KEY_LIST::SPACE))
		{
			createBullet();
		}
	}
	// �ӻ���
	else
	{
		if (ISPRESS(KEY_LIST::SPACE))
		{
			createBullet();
		}
	}

	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	while (iter != endIter)
	{
		(*iter)->update();
		++iter;
	}
}

bool CPlayer::collision()
{
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	while (iter != endIter)
	{
		if ((*iter)->collision())
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

	// �÷��̾�� �� �浹 ó��
	enemyCollision();

	// mCurrentHp �� 0 �� �Ǹ� �ٷ� ��Ʈ�� ȭ������ �̵�
	if (mCurrentHp <= 0)
	{
		return true;
	}
	return false;
}

void CPlayer::render(HDC backDC)
{
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	while (iter != endIter)
	{
		(*iter)->render(backDC);
		++iter;
	}

	SelectObject(backDC, GetStockObject(DC_BRUSH));

	static int hpBarX = (mMaxHp - mSize.x) / 2;

	// hp bar
	SetDCBrushColor(backDC, COLOR_RED);
	Rectangle(backDC, (int)mPos.mX - hpBarX, (int)mPos.mY + mSize.x + 5, (int)mPos.mX - hpBarX + mCurrentHp, (int)mPos.mY + mSize.x + 10);

	// mp bar
	SetDCBrushColor(backDC, COLOR_BLUE);
	Rectangle(backDC, (int)mPos.mX - hpBarX, (int)mPos.mY + mSize.x + 15, (int)mPos.mX - hpBarX + mCurrentMp, (int)mPos.mY + mSize.x + 20);

	SetDCBrushColor(backDC, COLOR_WHITE);

	// player
	// �Ʒ� �Լ��� DC -> DC �� ���縦 ���� �ϴµ� Ư�� �÷��� RGB �� ������ ������ �� �ִ�. �̸� �̿��� ����� �����Ѵ�.
	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}

void CPlayer::enemyCollision()
{
	list<CObj*>& objs = mLayer->getObjs();

	auto iter = objs.begin();
	auto endIter = objs.end();

	// �÷��̾�� ��
	while (iter != endIter)
	{
		if ((*iter)->getTag() == L"enemy" && CollisionManager::getInstance()->ractangleVsRactangle((*iter)->getCenter(), (*iter)->getRadius(), getCenter(), getRadius()))
		{
			CEnemy* enemy = (CEnemy*)(*iter);
			mCurrentHp -= enemy->getMaxHp();

			delete (*iter);

			iter = objs.erase(iter);
			endIter = objs.end();

			return;
		}
		else
		{
			++iter;
		}
	}
}

void CPlayer::createBullet()
{
	wstring wstag(L"defaultBullet1");
	Texture* texture = (Texture*)ResourceManager::getInstance()->findResource(wstag.c_str());

	float bulletPosX = float(mPos.mX + (mSize.x - texture->getResolution().x) / 2);
	float bulletPosY = mPos.mY;

	if (mBullets.empty())
	{
		mBullets.push_back(new CBullet(L"bullet", FPOINT{ bulletPosX, bulletPosY }, texture->getResolution(), texture, mLayer, mBulletSpeedWeight, mBulletOffencePower));
	}
	else
	{
		if (mBullets.front()->isValid())
		{
			mBullets.push_back(new CBullet(L"bullet", FPOINT{ bulletPosX, bulletPosY }, texture->getResolution(), texture, mLayer, mBulletSpeedWeight, mBulletOffencePower));
		}
		else
		{
			CBullet* invalidBullet = mBullets.front();
			mBullets.pop_front();

			invalidBullet->changePos(FPOINT{ bulletPosX ,bulletPosY });
			mBullets.push_back(invalidBullet);
		}
	}
}

void CPlayer::changeBulletWeight()
{
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	while (iter != endIter)
	{
		(*iter)->setSpeedWeight(mBulletSpeedWeight);
		++iter;
	}
}

