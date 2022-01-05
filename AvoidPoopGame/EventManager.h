#pragma once

#include "Game.h"

class EventManager
{
public:
	static EventManager* getInstance();
	static void deleteInstance();

	void init();

	void addEvent(EVENT_STATE eventState);
	void update();

private:
	EventManager() = default;
	~EventManager() = default;

	void ChangeStage(EVENT_STATE eventState);
	void CreateObj(EVENT_STATE eventState);
	void DeleteObj(EVENT_STATE eventState);

	static EventManager* mEventManager;
	vector<EVENT_STATE> mEvents;
};

