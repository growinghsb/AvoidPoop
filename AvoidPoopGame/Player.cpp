#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"

Player::Player()
	: Obj(FPOINT{}, 50)
	, mSpeed(200.f)
{
}

Player::Player(FPOINT pos, int size, float speed)
	: Obj(pos, size)
	, mSpeed(speed)
{
}

void Player::init()
{
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
}

void Player::render(HDC backDC)
{
	Rectangle(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mSize, (int)mPos.mY + mSize);
}
