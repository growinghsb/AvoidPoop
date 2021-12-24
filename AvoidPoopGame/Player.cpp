#include "Player.h"

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
}

void Player::render()
{
	
}
