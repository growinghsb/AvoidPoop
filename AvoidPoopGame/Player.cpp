#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Gun.h"
#include "Stage.h"
#include "Bullet.h"

Player::Player()
	: Obj(FPOINT{}, 50)
	, mSpeed(200.f)
	, mGun(nullptr)
{
}

Player::Player(FPOINT pos, int size, float speed)
	: Obj(pos, size)
	, mSpeed(speed)
	, mGun(nullptr)
{
}

Player::~Player()
{
	if (nullptr != mGun)
	{
		delete mGun;
		mGun = nullptr;
	}
}

void Player::init()
{
	if (nullptr == mGun)
	{
		mGun = new Gun(FPOINT{ mPos.mX + (mSize / 3), mPos.mY - mSize }, LENGTH{ mSize / 3, (int)mPos.mY });
	}
}

void Player::update()
{
	// 키 입력 이동 처리
	if (ISPRESS(KEY_LIST::LEFT))
	{
		mPos.mX -= mSpeed * DS;
	}

	if (ISPRESS(KEY_LIST::TOP))
	{
		mPos.mY -= mSpeed * DS;
	}

	if (ISPRESS(KEY_LIST::RIGHT))
	{
		mPos.mX += mSpeed * DS;
	}

	if (ISPRESS(KEY_LIST::BOTTOM))
	{
		mPos.mY += mSpeed * DS;
	}

	if (ISTIC(KEY_LIST::SPACE)) 
	{
		mGun->createBullet();
	}

	mGun->update(FPOINT{ mPos.mX + (mSize / 3), mPos.mY - mSize }, LENGTH{ mSize / 3, (int)mPos.mY });
}

void Player::render(HDC backDC)
{
	Rectangle(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mSize, (int)mPos.mY + mSize);
	mGun->render(backDC);
}
