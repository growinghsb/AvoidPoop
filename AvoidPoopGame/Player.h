#pragma once
#include "Obj.h"

class Player :
    public Obj
{
public:
	Player();
	Player(FPOINT pos, int size, float speed);
	~Player() = default;

	void init()   override;
	void update() override;
	void render(HDC backDC) override;

private:
	float mSpeed;
};

