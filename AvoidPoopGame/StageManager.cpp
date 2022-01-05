#include "StageManager.h"
#include "IntroStage.h"
#include "PlayStage.h"
#include "PlayStage2.h"

StageManager* StageManager::mStageManager = nullptr;

StageManager::StageManager()
	: mCurrentStage(nullptr)
	, mCurrentPlayer(nullptr)
{
	mStages.reserve(10);

	mStages.push_back(new IntroStage(0));
	mStages.push_back(new PlayStage(1));
	mStages.push_back(new PlayStage2(2));

	mCurrentStage = mStages[0];
}

StageManager::~StageManager()
{
	// 어짜피 소멸자이기 때문에 nullptr 초기화 안하고, 한 번에 클리어 해도 무방 
	for (size_t i = 0; i < mStages.size(); ++i)
	{
		delete mStages[i];
	}
	mStages.clear();
}

StageManager* StageManager::getInstance()
{
	if (nullptr == mStageManager)
	{
		mStageManager = new StageManager;
	}
	return mStageManager;
}

void StageManager::deleteInstance()
{
	if (nullptr != mStageManager)
	{
		delete mStageManager;
		mStageManager = nullptr;
	}
}

void StageManager::init()
{
	mCurrentStage->init();
}

void StageManager::update()
{
	mCurrentStage->update();
}

void StageManager::render(HDC backDC)
{
	mCurrentStage->render(backDC);
}

void StageManager::changeStage(STAGE_MODE mode)
{
	mCurrentStage->exit();

	int orderNum = mCurrentStage->getOrder();

	switch (mode)
	{
	case STAGE_MODE::INTRO:
		orderNum = 0;
		break;
	case STAGE_MODE::NEXT:
		orderNum += 1;
		break;
	case STAGE_MODE::PREV:
		orderNum -= 1;
		break;
	default:
		break;
	}

	mCurrentStage = mStages[orderNum];
	mCurrentStage->enter();
}

Stage* StageManager::getCurrentStage() const
{
	return mCurrentStage;
}
