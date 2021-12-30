#pragma once

#include "Game.h"

class CollisionManager
{
public:
	static CollisionManager* getInstance();
	static void deleteInstance();

	void init();

	bool circleVsCircle(FPOINT point1, int radius1, FPOINT point2, int radius2);
	bool ractangleVsRactangle(FPOINT pos1, int size1, FPOINT pos2, int size2);

private:
	CollisionManager() = default;
	~CollisionManager() = default;

	static CollisionManager* mCollisionManager;
};

