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
	// Ű �Է� �̵� ó��
}

void Player::render()
{
	
}
