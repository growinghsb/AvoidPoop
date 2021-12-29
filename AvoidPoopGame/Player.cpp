#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Gun.h"
#include "Stage.h"
#include "Bullet.h"
#include "Core.h"
#include "StageManager.h"
#include "Texture.h"

static int hpBarSize = 20;

Player::Player(FPOINT pos, int size, float speed, Texture* texture)
	: Obj(pos, size, "player")
	, mSpeed(speed)
	, mScale(1.0f)
	, mGun(new Gun(this, 400.f))
	, mLaunchMode(true)
	, mHP(100)
	, mHPBarColor{ 200, 0, 0 }
	, mTexture(texture)
{
	mSize = mTexture->getResolution().x;
}

Player::~Player()
{
	delete mGun;
	mGun = nullptr;
}

void Player::init()
{
}

void Player::update()
{
	// 키 입력 이동 처리
	if (ISPRESS(KEY_LIST::LEFT))
	{
		if ((int)mPos.mX > 0)
		{
			mPos.mX -= (mSpeed * DS) * mScale;
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
			mPos.mY -= (mSpeed * DS) * mScale;
		}
		else
		{
			mPos.mY = 0.f;
		}
	}

	if (ISPRESS(KEY_LIST::RIGHT))
	{
		if ((int)mPos.mX + mSize < WINDOW.right)
		{
			mPos.mX += (mSpeed * DS) * mScale;
		}
		else
		{
			mPos.mX = (float)WINDOW.right - (float)mSize;
		}
	}

	if (ISPRESS(KEY_LIST::BOTTOM))
	{
		if ((int)mPos.mY + mSize + hpBarSize < WINDOW.bottom)
		{
			mPos.mY += (mSpeed * DS) * mScale;
		}
		else
		{
			mPos.mY = (float)WINDOW.bottom - (float)mSize - hpBarSize;
		}
	}

	if (ISTIC(KEY_LIST::_1))
	{
		if ((int)mScale < 2)
		{
			mScale += 0.1f;
		}
		else
		{
			mScale = 1.9f;
		}
	}

	if (ISTIC(KEY_LIST::_2))
	{
		if ((int)mScale >= 1)
		{
			mScale -= 0.1f;
		}
		else
		{
			mScale = 1.0f;
		}
	}

	if (ISTIC(KEY_LIST::_3))
	{
		mGun->bulletScaleUp();
	}

	if (ISTIC(KEY_LIST::_4))
	{
		mGun->bulletScaleDown();
	}

	if (ISTIC(KEY_LIST::LSHIFT))
	{
		mLaunchMode ? mLaunchMode = false : mLaunchMode = true;
	}

	// 연사모드
	if (mLaunchMode)
	{
		if (ISTIC(KEY_LIST::SPACE))
		{
			mGun->createBullet();
		}
	}
	// 속사모드
	else
	{
		if (ISPRESS(KEY_LIST::SPACE))
		{
			mGun->createBullet();
		}
	}
	mGun->update();
}

void Player::render(HDC backDC)
{
	SelectObject(backDC, GetStockObject(DC_BRUSH));

	// hp bar
	static int hpBarX = (mHP - mSize) / 2;
	SetDCBrushColor(backDC, RGB(mHPBarColor.r, mHPBarColor.g, mHPBarColor.b));
	Rectangle(backDC, (int)mPos.mX - hpBarX, (int)mPos.mY + mSize + hpBarSize / 4, (int)mPos.mX - hpBarX + mHP, (int)mPos.mY + mSize + hpBarSize / 2);

	// player
	
	// 아래 함수는 일반적으로 DC -> DC 를 복사하는 함수이다.
	//BitBlt(backDC, (int)mPos.mX, (int)mPos.mY, mTexture->getResolution().x, mTexture->getResolution().y, mTexture->getTextureDC(), 0, 0, SRCCOPY);

	// 아래 함수는 DC -> DC 의 복사를 진행 하는데 특정 컬러를 RGB 로 지정해 제거할 수 있다. 이를 이용해 배경을 제거한다.
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, mTexture->getResolution().x, mTexture->getResolution().y, mTexture->getTextureDC(), 0, 0, mTexture->getResolution().x, mTexture->getResolution().y, COLOR_WHITE);

	mGun->render(backDC);
}

void Player::decreaseHP(int offensePower)
{
	mHP -= offensePower;
}
