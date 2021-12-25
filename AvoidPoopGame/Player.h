#pragma once
#include "Obj.h"

class Player :
    public Obj
{
public:
	Player();
	Player(FPOINT pos, int size, float speed);
	~Player();

	void init()				override;
	void update()			override;
	void render(HDC backDC) override;

private:
	float mSpeed;
	float mScale;
	bool mLaunchMode; // �ӻ�, ���� ��� ���� 
	class Gun* mGun;
};

