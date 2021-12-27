#pragma once
#pragma once

#include "Game.h"

class Stage
{
public:
	Stage(int order);
	virtual ~Stage() = default;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render(HDC backDC) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;

	int getOrder() const
	{
		return mOrder;
	}

	virtual void stageClear() = 0;

protected:
	// ��� �ڽ� ������������ ������,
	// �� ��° �������������� ���� �ε��� ��
	int mOrder;
};

