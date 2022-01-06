#include "EventManager.h"
#include "StageManager.h"

EventManager* EventManager::mEventManager = nullptr;

EventManager* EventManager::getInstance()
{
	if (nullptr == mEventManager)
	{
		mEventManager = new EventManager;
	}
	return mEventManager;
}

void EventManager::deleteInstance()
{
	if (nullptr != mEventManager)
	{
		delete mEventManager;
		mEventManager = nullptr;
	}
}

void EventManager::init()
{
}

void EventManager::addEvent(EVENT_STATE eventState)
{
	mEvents.push_back(eventState);
}

void EventManager::update()
{
	for (size_t i = 0; i < mEvents.size(); ++i)
	{
		switch (mEvents[i].mType)
		{
		case eEVENT_TYPE::CHANGE_STAGE:
			ChangeStage(mEvents[i]);
			goto EXIT;
			break;
		case eEVENT_TYPE::CREATE_OBJ:
			CreateObj(mEvents[i]);
			break;
		case eEVENT_TYPE::DELETE_OBJ:
			DeleteObj(mEvents[i]);
			break;
		default:
			break;
		}
	}

	EXIT:
	mEvents.clear();
}

void EventManager::ChangeStage(EVENT_STATE eventState)
{
	StageManager::getInstance()->changeStage((STAGE_MODE)eventState.mLow);
}

void EventManager::CreateObj(EVENT_STATE eventState)
{
}

void EventManager::DeleteObj(EVENT_STATE eventState)
{
}
