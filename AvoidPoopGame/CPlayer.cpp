#include "CPlayer.h"
#include "CEnemy.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Core.h"
#include "Texture.h"

CPlayer::CPlayer(wstring tag, FPOINT pos, POINT size, Texture* texture, float speed)
	: CObj(tag, pos, size, texture)
	, mSpeed(speed)
	, mSpeedWeight(1.0f)
	, mMaxHp(100)
	, mLaunchMode(true)
{
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
		// �Ѿ� �ӵ� ����
	}

	if (ISTIC(KEY_LIST::_4))
	{
		// �Ѿ� �ӵ� ����
	}

	if (ISTIC(KEY_LIST::LSHIFT))
	{
		mLaunchMode ? mLaunchMode = false : mLaunchMode = true;
	}

	// ������
	if (mLaunchMode)
	{
		if (ISTIC(KEY_LIST::SPACE))
		{
			// �Ѿ� �����
		}
	}
	// �ӻ���
	else
	{
		if (ISPRESS(KEY_LIST::SPACE))
		{
			// �Ѿ� �����
		}
	}
}

void CPlayer::render(HDC backDC)
{
	SelectObject(backDC, GetStockObject(DC_BRUSH));

	// hp bar
	static int hpBarX = (mMaxHp - mSize.x) / 2;

	SetDCBrushColor(backDC, COLOR_RED);
	Rectangle(backDC, (int)mPos.mX - hpBarX, (int)mPos.mY + mSize.x + 5, (int)mPos.mX - hpBarX + mMaxHp, (int)mPos.mY + mSize.x + 10);

	SetDCBrushColor(backDC, COLOR_WHITE);

	// player
	// �Ʒ� �Լ��� DC -> DC �� ���縦 ���� �ϴµ� Ư�� �÷��� RGB �� ������ ������ �� �ִ�. �̸� �̿��� ����� �����Ѵ�.
	POINT tRes = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, tRes.x, tRes.y, mTexture->getTextureDC(), 0, 0, tRes.x, tRes.y, COLOR_WHITE);
}

void CPlayer::collision()
{
}

void CPlayer::createBullet()
{
}

void CPlayer::itemCollision()
{
}

void CPlayer::enemyCollision()
{
}
