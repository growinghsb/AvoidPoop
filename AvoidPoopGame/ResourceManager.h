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

		if (iter != mResources.end()) 
		{
			return (*iter).second;
		}
		return nullptr; // 찾는 리소스가 없을 때
	}

private:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* mResourceManager;
	wstring mAbsolutePullPath;
	unordered_map<wstring, class CResource*> mResources;
	
	enum {RESOURCE_COUNT = 10};
	const wchar_t* mLoadResourceList[RESOURCE_COUNT];
};

