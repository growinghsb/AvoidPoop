#pragma once

#include "Game.h"

class ResourceManager
{
public:
	static ResourceManager* getInstance();
	static void deleteInstance();

	void init();
		 
	void roadTexture(const wchar_t* tag);
	void roadSound();

	wstring& getAbsolutePullpath()
	{
		return mAbsolutePullPath;
	}

	class CResource* findResource(const wchar_t* tag) 
	{
		auto iter = mResources.find(tag);
		return (*iter).second;
	}

private:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* mResourceManager;
	wstring mAbsolutePullPath;
	unordered_map<wstring, class CResource*> mResources;
	
	enum {RESOURCE_COUNT = 14};
	const wchar_t* mLoadResourceList[RESOURCE_COUNT];
};

