#include "CollisionManager.h"

CollisionManager* CollisionManager::mCollisionManager = nullptr;

CollisionManager* CollisionManager::getInstance()
{
	if (nullptr == mCollisionManager)
	{
		mCollisionManager = new CollisionManager;
	}
	return mCollisionManager;
}

void CollisionManager::deleteInstance()
{
	if (nullptr != mCollisionManager)
	{
		delete mCollisionManager;
		mCollisionManager = nullptr;
	}
}

bool CollisionManager::circleVsCircle(FPOINT point1, int radius1, FPOINT point2, int radius2)
{
	int x2 = abs(int(point1.mX - point2.mX));
	int y2 = abs(int(point1.mY - point2.mY));

	x2 *= x2;
	y2 *= y2;
	int x2y2 = x2 + y2;

	int radius = radius1 + radius2;
	radius *= radius;

	return x2y2 <= radius;
}

bool CollisionManager::ractangleVsRactangle(FPOINT pos1, int size1, FPOINT pos2, int size2)
{
	return	pos1.mX < pos2.mX + size2 &&
			pos1.mX + size1 > pos2.mX &&
			pos1.mY < pos2.mY + size2 &&
			pos1.mY + size1 > pos2.mY;
}
